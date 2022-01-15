#include "Pineapple/CameraInterface.hpp"

#include <tuple>

#include "Pineapple/Utils.hpp"

namespace Pineapple::ZED
{

std::tuple<sl::InitParameters, sl::RecordingParameters, sl::RuntimeParameters>
ToStereolabs(const CameraParameters& parameters)
{
    sl::InitParameters initParameters;
    initParameters.camera_image_flip = [parameters]()
        {
            switch (parameters.CameraFlip)
            {
            case FlipMode::OFF: return sl::FLIP_MODE::OFF;
            case FlipMode::ON: return sl::FLIP_MODE::ON;
            case FlipMode::AUTO: return sl::FLIP_MODE::AUTO;
            default: return sl::FLIP_MODE::OFF;
            }
        }();
    initParameters.camera_resolution = [parameters]()
        {
            switch (parameters.CameraResolution)
            {
            case Resolution::HD2K: return sl::RESOLUTION::HD2K;
            case Resolution::HD1080: return sl::RESOLUTION::HD1080;
            case Resolution::HD720: return sl::RESOLUTION::HD720;
            case Resolution::VGA: return sl::RESOLUTION::VGA;
            default: return sl::RESOLUTION::HD720;
            }
        }();
    initParameters.camera_fps = parameters.CameraFPS;
    initParameters.open_timeout_sec = parameters.OpenTimeout;
    initParameters.enable_image_enhancement = parameters.EnableImageEnhancement;
    initParameters.camera_disable_self_calib =
        parameters.DisableSelfCalibration;
    initParameters.sensors_required = parameters.RequireSensors;

    sl::RecordingParameters recordingParameters;
    recordingParameters.compression_mode = [parameters]() 
        {
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

    return { initParameters, recordingParameters, runtimeParameters };
}

CameraInterface::CameraInterface(const std::filesystem::path& dataDirectory)
    : m_DataDirectory(dataDirectory)
{
}

CameraInterface::~CameraInterface() {}

void CameraInterface::StartRecord()
{
    m_StopFlag = false;
    m_WorkerThread = 
        std::make_unique<std::thread>(&CameraInterface::RecordWorker, this);
}

void CameraInterface::StopRecord()
{
    m_StopFlag = true;
    if (m_WorkerThread->joinable())
    {
        m_WorkerThread->join();
    }
}

void CameraInterface::RecordWorker()
{
    sl::Camera camera;

    auto [initParameters, recordingParameters, runtimeParameters] 
        = ToStereolabs(m_CameraParameters);

    const auto directory = m_DataDirectory;
    const auto dateString = CurrentDateTime() + ".svo";
    const auto filepath = directory / dateString;
    PINE_INFO("Recording: {0}", filepath);
    recordingParameters.video_filename = filepath.string().c_str();

    const auto openState = camera.open(initParameters);
    if (openState != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Opening ZED failed: {0}", toString(openState).get());
        return;
    }

    const auto enableState = camera.enableRecording(recordingParameters);
    if (enableState != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Enabling ZED recording failed: {0}", 
            toString(enableState).get());
        return;
    }

    while (!m_StopFlag)
    {
        const auto grabState = camera.grab(runtimeParameters);
        if (grabState != sl::ERROR_CODE::SUCCESS)
        {
            PINE_WARN("Grabbing record failed: {0}", toString(grabState).get());
        }
    }

    camera.close();
}

} // namespace Pineapple::ZED
