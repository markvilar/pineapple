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

class CameraInterface
{

public:
    CameraInterface(const std::filesystem::path& dataDirectory = ".");
    ~CameraInterface();

    void StartRecord();
    void StopRecord();

    std::optional<CameraSettings> GetCameraSettings();
    std::optional<IMUData> GetIMUData();
    std::optional<Pine::Image> GetImage(const uint32_t width,
        const uint32_t height, const View& view = View::LEFT);

private:
    void RecordWorker();

private:
    std::filesystem::path m_DataDirectory = "";
    CameraParameters m_CameraParameters = {};
    CameraSettings m_CameraSettings = {};

    sl::Camera m_Camera = {};

    std::unique_ptr<std::thread> m_WorkerThread = {};
    std::mutex m_CameraMutex = {};
    std::atomic<bool> m_StopFlag = false;
    std::atomic<bool> m_IsRecording = false;
};

} // namespace Pineapple::ZED
