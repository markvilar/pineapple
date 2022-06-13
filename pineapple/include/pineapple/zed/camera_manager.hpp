#pragma once

#ifdef PINEAPPLE_ENABLE_ZED

#include <cstdint>
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

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

namespace pineapple::zed
{

struct RecordJob
{
    std::filesystem::path output_directory = "";
    CameraParameters parameters = {};
};

// ----------------------------------------------------------------------------
// Record manager
// ----------------------------------------------------------------------------

class RecordManager
{
public:
    RecordManager(const std::filesystem::path& output_directory = ".");
    ~RecordManager();

    void start_record(const CameraParameters& parameters = {});
    void start_record(const CameraParameters& parameters,
        const std::filesystem::path& output_directory);

    void stop_record();

    bool is_opened();
    bool is_recording();
    bool is_stopped();

    uint64_t get_total_space();
    uint64_t get_free_space();
    uint64_t get_available_space();

    std::optional<CameraSettings> request_camera_settings();
    std::optional<SensorData> request_sensor_data();
    std::optional<Image> request_image(const uint32_t width,
        const uint32_t height, const View view = View::LEFT);

    bool update_camera_settings(const CameraSettings& settings);

private:
    void record_worker(const RecordJob job);

private:
    std::filesystem::path m_output_directory = ".";

    sl::Camera m_camera = {};

    std::unique_ptr<std::thread> m_worker_thread = {};
    std::atomic<bool> m_stop_flag = false;
    std::atomic<bool> m_busy_flag = false;
};

// ----------------------------------------------------------------------------
// Camera manager
// ----------------------------------------------------------------------------

class CameraManager
{
public:
    CameraManager(const uint16_t port,
        const std::filesystem::path& outputDirectory = ".");
    ~CameraManager();

    void run();

private:
    void on_update();
    void on_message(const std::vector<uint8_t>& buffer);

    void on_request(const zed::ControlService::Request::DataType& request);
    void on_request(const zed::ImageService::Request::DataType& request);
    void on_request(const zed::MemoryService::Request::DataType& request);
    void on_request(const zed::SensorService::Request::DataType& request);
    void on_request(const zed::SettingsService::Request::DataType& request);

private:
    bool m_running = true;

    Pine::ServerState m_server;

    RecordManager m_record_manager;
    // TODO: Add video stream manager
    // TODO: Add depth manager
};

}; // namespace pineapple::zed

#endif // PINEAPPLE_ENABLE_ZED
