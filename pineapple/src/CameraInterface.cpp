#include "Pineapple/CameraInterface.hpp"

#include <tuple>

#include "Pineapple/Utils.hpp"

namespace Pineapple::ZED
{

std::tuple<sl::InitParameters, sl::RecordingParameters, sl::RuntimeParameters>
ToStereolabs(const CameraParameters& parameters)
{
    sl::InitParameters initParameters;
    initParameters.camera_image_flip = [parameters]() {
        switch (parameters.CameraFlip)
        {
        case FlipMode::OFF:
            return sl::FLIP_MODE::OFF;
        case FlipMode::ON:
            return sl::FLIP_MODE::ON;
        case FlipMode::AUTO:
            return sl::FLIP_MODE::AUTO;
        default:
            return sl::FLIP_MODE::OFF;
        }
    }();
    initParameters.camera_resolution = [parameters]() {
        switch (parameters.CameraResolution)
        {
        case Resolution::HD2K:
            return sl::RESOLUTION::HD2K;
        case Resolution::HD1080:
            return sl::RESOLUTION::HD1080;
        case Resolution::HD720:
            return sl::RESOLUTION::HD720;
        case Resolution::VGA:
            return sl::RESOLUTION::VGA;
        default:
            return sl::RESOLUTION::HD720;
        }
    }();
    initParameters.camera_fps = parameters.CameraFPS;
    initParameters.open_timeout_sec = parameters.OpenTimeout;
    initParameters.enable_image_enhancement = parameters.EnableImageEnhancement;
    initParameters.camera_disable_self_calib =
        parameters.DisableSelfCalibration;
    initParameters.sensors_required = parameters.RequireSensors;

    sl::RecordingParameters recordingParameters;
    recordingParameters.compression_mode = [parameters]() {
        switch (parameters.Compression)
        {
        case CompressionMode::LOSSLESS:
            return sl::SVO_COMPRESSION_MODE::LOSSLESS;
        case CompressionMode::H264:
            return sl::SVO_COMPRESSION_MODE::H264;
        case CompressionMode::H265:
            return sl::SVO_COMPRESSION_MODE::H265;
        default:
            return sl::SVO_COMPRESSION_MODE::H264;
        }
    }();

    sl::RuntimeParameters runtimeParameters;
    runtimeParameters.enable_depth = parameters.EnableDepth;

    return {initParameters, recordingParameters, runtimeParameters};
}

CameraInterface::CameraInterface(const std::filesystem::path& dataDirectory)
    : m_OutputDirectory(dataDirectory)
{
}

CameraInterface::~CameraInterface() { StopRecord(); }

void CameraInterface::StartRecord(const CameraParameters& parameters)
{
    StartRecord(parameters, m_OutputDirectory);
}

void CameraInterface::StartRecord(const CameraParameters& parameters,
    const std::filesystem::path& outputDirectory)
{
    if (!m_Busy.exchange(true))
    {
        PINE_WARN("ZED camera is already recording.");
        return;
    }

    RecordJob job;
    job.OutputDirectory = outputDirectory;
    job.Parameters = parameters;

    m_WorkerThread =
        std::make_unique<std::thread>(&CameraInterface::RecordWorker,
            this,
            job);
}

void CameraInterface::StopRecord()
{
    m_Stop = true;
    if (m_WorkerThread->joinable())
    {
        m_WorkerThread->join();
    }
}

std::optional<CameraSettings> CameraInterface::GetCameraSettings()
{
    if (!m_Camera.isOpened())
    {
        PINE_WARN("ZED is not opened - cannot get settings.");
        return {};
    }

    CameraSettings settings;
    settings.Brightness =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS);
    settings.Contrast =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::CONTRAST);
    settings.Hue = m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::HUE);
    settings.Saturation =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::SATURATION);
    settings.Sharpness =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::SHARPNESS);
    settings.Gain = m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::GAIN);
    settings.Exposure =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE);
    settings.Whitebalance = m_Camera.getCameraSettings(
        sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE);
    settings.AutoExposure =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC);
    settings.AutoWhitebalance =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO);
    settings.EnableLED =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS);

    return settings;
}

std::optional<IMUData> CameraInterface::GetIMUData()
{
    if (!m_Camera.isOpened())
    {
        PINE_WARN("ZED is not opened - cannot get IMU data.");
        return {};
    }

    sl::SensorsData nativeData;
    m_Camera.getSensorsData(nativeData, sl::TIME_REFERENCE::CURRENT);

    auto timestamp = nativeData.imu.timestamp.getNanoseconds();
    auto acceleration = nativeData.imu.linear_acceleration;
    auto angularVelocity = nativeData.imu.angular_velocity;

    Pineapple::IMUData data;
    data.Timestamp = timestamp;
    data.Acceleration =
        Pine::Vec3(acceleration[0], acceleration[1], acceleration[2]);
    data.AngularVelocity =
        Pine::Vec3(angularVelocity[0], angularVelocity[1], angularVelocity[2]);

    return data;
}

std::optional<Pine::Image> CameraInterface::GetImage(
    const uint32_t width, const uint32_t height, const View& view)
{
    if (!m_Camera.isOpened())
    {
        PINE_WARN("ZED is not opened - cannot get image.");
        return {};
    }

    const auto nativeView = [view]() {
        switch (view)
        {
        case View::LEFT:
            return sl::VIEW::LEFT;
        case View::RIGHT:
            return sl::VIEW::RIGHT;
        case View::LEFT_GRAY:
            return sl::VIEW::LEFT_GRAY;
        case View::RIGHT_GRAY:
            return sl::VIEW::RIGHT_GRAY;
        case View::SIDE_BY_SIDE:
            return sl::VIEW::SIDE_BY_SIDE;
        default:
            return sl::VIEW::LEFT;
        }
    }();

    const auto imageFormat = [view]() {
        switch (view)
        {
        case View::LEFT:
            return Pine::ImageFormat::BGRA;
        case View::RIGHT:
            return Pine::ImageFormat::BGRA;
        case View::LEFT_GRAY:
            return Pine::ImageFormat::GRAY;
        case View::RIGHT_GRAY:
            return Pine::ImageFormat::GRAY;
        case View::SIDE_BY_SIDE:
            return Pine::ImageFormat::BGRA;
        default:
            return Pine::ImageFormat::BGRA;
        }
    }();

    sl::Mat nativeImage;
    m_Camera.retrieveImage(nativeImage,
        nativeView,
        sl::MEM::CPU,
        sl::Resolution(width, height));

    Pine::Image image(nativeImage.getPtr<uint8_t>(),
        nativeImage.getWidth(),
        nativeImage.getHeight(),
        imageFormat);

    return image;
}

void CameraInterface::RecordWorker(const RecordJob job)
{
    auto [initParameters, recordingParameters, runtimeParameters] =
        ToStereolabs(job.Parameters);

    const auto dateString = CurrentDateTime() + ".svo";
    const auto filepath = job.OutputDirectory / dateString;
    PINE_INFO("Starting record job: {0}", filepath);
    recordingParameters.video_filename = filepath.string().c_str();

    const auto openState = m_Camera.open(initParameters);
    if (openState != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while opening ZED: {0}",
            sl::toString(openState).get());
        m_Busy = false;
        return;
    }

    const auto enableState = m_Camera.enableRecording(recordingParameters);
    if (enableState != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while enabling ZED recording: {0}",
            sl::toString(enableState).get());
        m_Busy = false;
        return;
    }

    while (!m_Stop)
    {
        const auto grabState = m_Camera.grab(runtimeParameters);
        if (grabState != sl::ERROR_CODE::SUCCESS)
        {
            PINE_WARN("Error while grabbing ZED data: {0}",
                sl::toString(grabState).get());
        }
    }

    m_Camera.close();
    m_Busy = false;
    m_Stop = false;
}

} // namespace Pineapple::ZED
