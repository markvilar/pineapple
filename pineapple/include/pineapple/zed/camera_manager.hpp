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

#include <pine/pine.hpp>

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

namespace zed
{

struct RecordJob
{
    std::filesystem::path output_directory = ".";
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

    std::optional<CameraSettings> get_settings();
    std::optional<SensorData> get_sensor_data();
    std::optional<Image> get_image(const uint32_t width, const uint32_t height);

    bool update_settings(const CameraSettings& settings);

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

    template <typename T>
    void send_message(const std::shared_ptr<pine::ConnectionState>& client,
        const T& message)
    {
        msgpack::sbuffer buffer;
        msgpack::pack(buffer, message);
        pine::send_to_client(server,
            client,
            (uint8_t*)buffer.data(),
            buffer.size());
    }

    void on_message(const std::vector<uint8_t>& buffer);

    void on_message(const zed::ControlMessage& message);
    void on_message(const zed::SettingsMessage& message);
    void on_message(const zed::SensorMessage& message);
    void on_message(const zed::StreamMessage& message);

private:
    bool running = true;
    bool streaming = false;

    // FIXME: timestamps
    std::chrono::time_point<std::chrono::high_resolution_clock> last_frame =
        std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> now =
        std::chrono::high_resolution_clock::now();

    uint16_t stream_width = 0;
    uint16_t stream_height = 0;
    float stream_period = 1.0f;

    pine::ServerState server;
    RecordManager record_manager;
};

}; // namespace zed

#endif // PINEAPPLE_ENABLE_ZED
