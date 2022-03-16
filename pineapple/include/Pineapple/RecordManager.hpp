#pragma once

#include <filesystem>
#include <mutex>
#include <optional>
#include <queue>
#include <tuple>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wcpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wcpp"
#include <sl/Camera.hpp>

#include <Pine/Pine.hpp>

#include "Pineapple/CameraControls.hpp"
#include "Pineapple/SensorData.hpp"

namespace Pineapple::ZED
{

struct RecordJob
{
    std::filesystem::path OutputDirectory = "";
    CameraParameters Parameters = {};
};

class RecordManager
{
    using Image = Pine::Image;

public:
    RecordManager(const std::filesystem::path& outputDirectory = ".");
    ~RecordManager();

    void StartRecord(const CameraParameters& parameters = {});
    void StartRecord(const CameraParameters& parameters,
        const std::filesystem::path& outputDirectory);

    void StopRecord();

    std::optional<CameraSettings> RequestCameraSettings();
    std::optional<IMUData> RequestIMUData();
    std::optional<Image> RequestImage(const uint32_t width, 
        const uint32_t height, const View& view = View::LEFT);

    bool UpdateCameraSettings(const CameraSettings& settings);

private:
    void RecordWorker(const RecordJob job);

private:
    std::filesystem::path m_OutputDirectory = ".";
    CameraSettings m_CameraSettings = {};

    sl::Camera m_Camera = {};

    std::unique_ptr<std::thread> m_WorkerThread = {};
    std::mutex m_CameraMutex = {}; // Not used.

    std::atomic<bool> m_Stop = false;
    std::atomic<bool> m_Busy = false;
};

} // namespace Pineapple::ZED
