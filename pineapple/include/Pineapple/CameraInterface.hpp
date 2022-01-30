#pragma once

#include <filesystem>
#include <mutex>
#include <queue>
#include <tuple>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <sl/Camera.hpp>

#include "Pine/Pine.hpp"

#include "Pineapple/CameraParameters.hpp"
#include "Pineapple/CameraSettings.hpp"
#include "Pineapple/Image.hpp"

namespace Pineapple::ZED
{

class CameraInterface
{

public:
    CameraInterface(const std::filesystem::path& dataDirectory=".");
    ~CameraInterface();

    void StartRecord();
    void StopRecord();

    /*
    std::optional<CameraSettings> GetCameraSettings();

    std::optional<std::shared_ptr<Pineapple::Image<uint8_t>>> GetImage(
        const View& view = View::Left);

    std::optional<IMUData> GetIMUData();
    */
private:
    void RecordWorker();

private:
    std::filesystem::path m_DataDirectory = "";

    CameraParameters m_CameraParameters = {};
    CameraSettings m_CameraSettings = {};

    // TODO: Add queues for actions, settings, images, and IMU entries.

    std::unique_ptr<std::thread> m_WorkerThread = {};
    std::queue<uint32_t> m_WorkerInQueue = {};
    std::queue<uint32_t> m_WorkerOutQueue = {};
    std::atomic<bool> m_StopFlag = false;
};

} // namespace Pineapple::ZED
