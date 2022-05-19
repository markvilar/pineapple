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

#include "Pineapple/Zed/Types.hpp"

namespace Pineapple::Zed
{

struct RecordJob
{
    std::filesystem::path output_directory = "";
    CameraParameters parameters = {};
};

class RecordManager
{
public:
    RecordManager(const std::filesystem::path& output_directory = ".");
    ~RecordManager();

    void StartRecord(const CameraParameters& parameters = {});
    void StartRecord(const CameraParameters& parameters,
        const std::filesystem::path& output_directory);

    void StopRecord();

    bool IsOpened();
    bool IsRecording();
    bool IsStopped();

    uint64_t GetTotalSpace();
    uint64_t GetFreeSpace();
    uint64_t GetAvailableSpace();

    std::optional<CameraSettings> RequestCameraSettings();
    std::optional<SensorData> RequestSensorData();
    std::optional<Image> RequestImage(const uint32_t width, 
        const uint32_t height, const View view = View::LEFT);

    bool UpdateCameraSettings(const CameraSettings& settings);

private:
    void RecordWorker(const RecordJob job);

private:
    std::filesystem::path m_OutputDirectory = ".";

    sl::Camera m_Camera = {};

    std::unique_ptr<std::thread> m_WorkerThread = {};
    std::atomic<bool> m_Stop = false;
    std::atomic<bool> m_Busy = false;
};

} // namespace Pineapple::Zed