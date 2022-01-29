#pragma once

#include <filesystem>
#include <mutex>
#include <optional>
#include <queue>
#include <tuple>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <sl/Camera.hpp>

#include <Pine/Pine.hpp>

#include "Pineapple/CameraParameters.hpp"
#include "Pineapple/CameraSettings.hpp"
#include "Pineapple/IMU.hpp"
#include "Pineapple/Image.hpp"

namespace Pineapple::ZED
{

struct RecordJob
{
    std::filesystem::path OutputDirectory = "";
    CameraParameters Parameters = {};
};

class CameraInterface
{
    using Image = Pine::Image;

public:
    CameraInterface(const std::filesystem::path& outputDirectory = ".");
    ~CameraInterface();

    void StartRecord(const CameraParameters& parameters = {});
    void StartRecord(const CameraParameters& parameters,
        const std::filesystem::path& outputDirectory);

    void StopRecord();

    std::optional<CameraSettings> GetCameraSettings();
    std::optional<IMUData> GetIMUData();
    std::optional<Image> GetImage(const uint32_t width, const uint32_t height,
        const View& view = View::LEFT);

private:
    void RecordWorker(const RecordJob job);

private:
    std::filesystem::path m_OutputDirectory = ".";
    CameraSettings m_CameraSettings = {};

    sl::Camera m_Camera = {};

    std::unique_ptr<std::thread> m_WorkerThread = {};
    std::mutex m_CameraMutex = {};
    std::atomic<bool> m_Stop = false;
    std::atomic<bool> m_Busy = false;
};

} // namespace Pineapple::ZED
