#include "pineapple/zed/camera_manager.hpp"

#include "pineapple/zed/protocol.hpp"
#include "pineapple/utils.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace pineapple::zed
{

std::tuple<sl::InitParameters, sl::RecordingParameters, sl::RuntimeParameters>
ToStereolabs(const CameraParameters& parameters)
{
    sl::InitParameters init_parameters;
    init_parameters.camera_resolution = [parameters]() {
        switch (parameters.resolution)
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
    init_parameters.camera_fps = parameters.fps;
    init_parameters.open_timeout_sec = parameters.timeout;
    init_parameters.enable_image_enhancement = 
        parameters.enable_image_enhancement;
    init_parameters.camera_disable_self_calib =
        parameters.disable_self_calibration;
    init_parameters.sensors_required = parameters.require_sensors;

    sl::RecordingParameters recording_parameters;
    recording_parameters.compression_mode = [parameters]() {
        switch (parameters.compression)
        {
        case Compression::LOSSLESS:
            return sl::SVO_COMPRESSION_MODE::LOSSLESS;
        case Compression::H264:
            return sl::SVO_COMPRESSION_MODE::H264;
        case Compression::H265:
            return sl::SVO_COMPRESSION_MODE::H265;
        case Compression::H264_LOSSLESS:
            return sl::SVO_COMPRESSION_MODE::H264_LOSSLESS;
        case Compression::H265_LOSSLESS:
            return sl::SVO_COMPRESSION_MODE::H265_LOSSLESS;
        default:
            return sl::SVO_COMPRESSION_MODE::H264;
        }
    }();

    sl::RuntimeParameters runtime_parameters;
    runtime_parameters.enable_depth = parameters.enable_depth;

    return {init_parameters, recording_parameters, runtime_parameters};
}

RecordManager::RecordManager(const std::filesystem::path& output_directory)
    : m_OutputDirectory(output_directory)
{
}

RecordManager::~RecordManager() { StopRecord(); }

void RecordManager::StartRecord(const CameraParameters& parameters)
{
    StartRecord(parameters, m_OutputDirectory);
}

void RecordManager::StartRecord(const CameraParameters& parameters,
    const std::filesystem::path& output_directory)
{
    if (m_Busy.exchange(true))
    {
        PINE_WARN("Zed camera busy.");
        return;
    }

    if (m_WorkerThread && m_WorkerThread->joinable())
    {
        m_WorkerThread->join();
    }

    RecordJob job;
    job.output_directory = output_directory;
    job.parameters = parameters;
    
    m_Stop = false;

    m_WorkerThread =
        std::make_unique<std::thread>(&RecordManager::RecordWorker,
            this,
            job);
}

void RecordManager::StopRecord()
{
    if (m_Stop.exchange(true))
    {
        return;
    }

    if (m_WorkerThread && m_WorkerThread->joinable())
    {
        m_WorkerThread->join();
    }
}

bool RecordManager::IsOpened()
{
    return m_Camera.isOpened();
}

bool RecordManager::IsRecording()
{
    if (!IsOpened())
    {
        return false;
    }
    return m_Camera.getRecordingStatus().is_recording;
}

bool RecordManager::IsStopped()
{
    return m_Stop.load();
}

uint64_t RecordManager::GetTotalSpace()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_OutputDirectory, error);
    return si.capacity;
}

uint64_t RecordManager::GetFreeSpace()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_OutputDirectory, error);
    return si.free;
}

uint64_t RecordManager::GetAvailableSpace()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_OutputDirectory, error);
    return si.available;
}

std::optional<CameraSettings> RecordManager::RequestCameraSettings()
{
    if (!m_Camera.isOpened())
    {
        return {};
    }

    CameraSettings settings;
    settings.brightness =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS);
    settings.contrast =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::CONTRAST);
    settings.hue = m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::HUE);
    settings.saturation =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::SATURATION);
    settings.sharpness =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::SHARPNESS);
    settings.gain = m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::GAIN);
    settings.exposure =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE);
    settings.whitebalance = m_Camera.getCameraSettings(
        sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE);
    settings.auto_exposure =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC);
    settings.auto_whitebalance =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO);
    settings.enable_led =
        m_Camera.getCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS);

    return settings;
}

std::optional<SensorData> RecordManager::RequestSensorData()
{
    if (!m_Camera.isOpened())
    {
        return {};
    }

    sl::SensorsData native_data;
    m_Camera.getSensorsData(native_data, sl::TIME_REFERENCE::CURRENT);

    auto& acceleration = native_data.imu.linear_acceleration;
    auto& angular_velocity = native_data.imu.angular_velocity;
    auto& temperatures = native_data.temperature.temperature_map;

    pineapple::zed::SensorData data;
    data.pressure = native_data.barometer.pressure * 100.0f;
    data.temperature_left = temperatures[sl::SensorsData::TemperatureData::SENSOR_LOCATION::ONBOARD_LEFT];
    data.temperature_right = temperatures[sl::SensorsData::TemperatureData::SENSOR_LOCATION::ONBOARD_RIGHT];
    data.acceleration =
        Pine::Vec3(acceleration[0], acceleration[1], acceleration[2]);
    data.angular_velocity =
        Pine::Vec3(angular_velocity[0], angular_velocity[1], angular_velocity[2]);

    return data;
}

std::optional<Image> RecordManager::RequestImage(
    const uint32_t width, const uint32_t height, const View view)
{
    if (!m_Camera.isOpened())
    {
        return {};
    }

    const auto native_view = [view]() {
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

    sl::Mat native_image;
    m_Camera.retrieveImage(native_image,
        native_view,
        sl::MEM::CPU,
        sl::Resolution(width, height));

    Image image(native_image.getPtr<uint8_t>(), native_image.getWidth(),
        native_image.getHeight(), view);

    return std::move(image);
}

bool RecordManager::UpdateCameraSettings(const CameraSettings& settings)
{
    if (!m_Camera.isOpened())
    {
        return false;
    }

    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS,
        settings.brightness);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::CONTRAST,
        settings.contrast);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::HUE,
        settings.hue);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::SATURATION,
        settings.saturation);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::SHARPNESS,
        settings.sharpness);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::GAMMA,
        settings.gamma);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::GAIN,
        settings.gain);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE,
        settings.exposure);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE,
        settings.whitebalance);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC,
        settings.auto_exposure);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO,
        settings.auto_whitebalance);
    m_Camera.setCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS,
        settings.enable_led);
    return true;
}

void RecordManager::RecordWorker(const RecordJob job)
{
    auto [init_parameters, recording_parameters, runtime_parameters] =
        ToStereolabs(job.parameters);

    const auto date_string = CurrentDateTime() + ".svo";
    const auto filepath = job.output_directory / date_string;
    recording_parameters.video_filename = filepath.string().c_str();

    const auto open_state = m_Camera.open(init_parameters);
    if (open_state != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while opening Zed: {0}",
            sl::toString(open_state).get());
        m_Busy = false;
        return;
    }

    const auto recording_state = m_Camera.enableRecording(recording_parameters);
    if (recording_state != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while enabling Zed recording: {0}",
            sl::toString(recording_state).get());
        m_Busy = false;
        return;
    }

    while (!m_Stop)
    {
        const auto grab_state = m_Camera.grab(runtime_parameters);
        if (grab_state != sl::ERROR_CODE::SUCCESS)
        {
            PINE_WARN("Error while grabbing Zed data: {0}",
                sl::toString(grab_state).get());
        }
    }

    m_Camera.close();
    m_Busy = false;
}

CameraManager::CameraManager(const uint16_t port, 
    const std::filesystem::path& outputDirectory)
    : m_Server(port), m_RecordManager(outputDirectory)
{
}

CameraManager::~CameraManager()
{
    PINE_INFO("Stopping server.");
    StopServer(m_Server);
}

void CameraManager::Run()
{
    Pine::StartServer(m_Server, 
        [this](const Pine::ConnectionState& connection) -> bool
        {
            PINE_INFO("Server got connection: {0}", 
                connection.Socket.remote_endpoint());
            return true;
        });

    while (m_Running)
    {
        OnUpdate();
    }
}

void CameraManager::OnUpdate()
{
    Pine::UpdateServer(m_Server, 
        [this](const Pine::Message& message) -> void
        {
            OnMessage(message);
        });
}

void CameraManager::OnMessage(const Pine::Message& message)
{
    PINE_INFO("Got message: {0}", message.Header.Size);
}

}; // namespace pineapple::zed

#endif // PINEAPPLE_ENABLE_ZED
