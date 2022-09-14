#include "pineapple/zed/camera_manager.hpp"

#include <chrono>

#include "pineapple/utils.hpp"
#include "pineapple/zed/protocol.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace zed
{

std::tuple<sl::InitParameters, sl::RecordingParameters, sl::RuntimeParameters>
to_stereolabs(const CameraParameters& parameters)
{
    sl::InitParameters init_parameters;
    init_parameters.camera_resolution = [parameters]()
    {
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
    recording_parameters.compression_mode = [parameters]()
    {
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
    : m_output_directory(output_directory)
{
}

RecordManager::~RecordManager() { stop_record(); }

void RecordManager::start_record(const CameraParameters& parameters)
{
    start_record(parameters, m_output_directory);
}

void RecordManager::start_record(const CameraParameters& parameters,
    const std::filesystem::path& output_directory)
{
    if (m_busy_flag.exchange(true))
    {
        PINE_WARN("Zed camera busy.");
        return;
    }

    if (m_worker_thread && m_worker_thread->joinable())
    {
        m_worker_thread->join();
    }

    RecordJob job;
    job.output_directory = output_directory;
    job.parameters = parameters;

    m_stop_flag = false;

    m_worker_thread =
        std::make_unique<std::thread>(&RecordManager::record_worker, this, job);
}

void RecordManager::stop_record()
{
    if (m_stop_flag.exchange(true))
    {
        return;
    }

    if (m_worker_thread && m_worker_thread->joinable())
    {
        m_worker_thread->join();
    }
}

bool RecordManager::is_opened() { return m_camera.isOpened(); }

bool RecordManager::is_recording()
{
    if (!is_opened())
    {
        return false;
    }
    return m_camera.getRecordingStatus().is_recording;
}

bool RecordManager::is_stopped() { return m_stop_flag.load(); }

uint64_t RecordManager::get_total_space()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_output_directory, error);
    return si.capacity;
}

uint64_t RecordManager::get_free_space()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_output_directory, error);
    return si.free;
}

uint64_t RecordManager::get_available_space()
{
    std::error_code error;
    const auto si = std::filesystem::space(m_output_directory, error);
    return si.available;
}

std::optional<CameraSettings> RecordManager::get_settings()
{
    if (!is_opened())
    {
        return {};
    }

    CameraSettings settings;
    settings.brightness =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS);
    settings.contrast =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::CONTRAST);
    settings.hue = m_camera.getCameraSettings(sl::VIDEO_SETTINGS::HUE);
    settings.saturation =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::SATURATION);
    settings.sharpness =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::SHARPNESS);
    settings.gain = m_camera.getCameraSettings(sl::VIDEO_SETTINGS::GAIN);
    settings.exposure =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE);
    settings.whitebalance = m_camera.getCameraSettings(
        sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE);
    settings.auto_exposure =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC);
    settings.auto_whitebalance =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO);

    return settings;
}

std::optional<SensorData> RecordManager::get_sensor_data()
{
    if (!is_opened())
    {
        return {};
    }

    sl::SensorsData native_data;
    m_camera.getSensorsData(native_data, sl::TIME_REFERENCE::CURRENT);

    auto& acceleration = native_data.imu.linear_acceleration;
    auto& turnrate = native_data.imu.angular_velocity;
    auto& temperatures = native_data.temperature.temperature_map;

    zed::SensorData data;
    data.pressure = native_data.barometer.pressure * 100.0f;
    data.temperature_left = temperatures
        [sl::SensorsData::TemperatureData::SENSOR_LOCATION::ONBOARD_LEFT];
    data.temperature_right = temperatures
        [sl::SensorsData::TemperatureData::SENSOR_LOCATION::ONBOARD_RIGHT];
    data.acceleration =
        pine::Vec3(acceleration[0], acceleration[1], acceleration[2]);
    data.turnrate = pine::Vec3(turnrate[0], turnrate[1], turnrate[2]);

    return data;
}

std::optional<Image> RecordManager::get_image(const uint32_t width,
    const uint32_t height)
{
    if (!is_opened())
    {
        return {};
    }

    sl::Mat native_image;
    m_camera.retrieveImage(native_image,
        sl::VIEW::LEFT,
        sl::MEM::CPU,
        sl::Resolution(width, height));

    Image image(native_image.getPtr<uint8_t>(),
        native_image.getWidth(),
        native_image.getHeight(),
        4);

    return std::move(image);
}

bool RecordManager::update_settings(const CameraSettings& settings)
{
    if (!is_opened())
    {
        return false;
    }

    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS,
        settings.brightness);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::CONTRAST, settings.contrast);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::HUE, settings.hue);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::SATURATION,
        settings.saturation);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::SHARPNESS,
        settings.sharpness);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::GAMMA, settings.gamma);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::GAIN, settings.gain);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE, settings.exposure);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE,
        settings.whitebalance);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC,
        settings.auto_exposure);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO,
        settings.auto_whitebalance);
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS, false);

    return true;
}

void RecordManager::record_worker(const RecordJob job)
{
    auto [init_parameters, recording_parameters, runtime_parameters] =
        to_stereolabs(job.parameters);

    const auto date_string =
        pineapple::current_date_time() + std::string(".svo");
    const auto filepath = job.output_directory / date_string;
    recording_parameters.video_filename = filepath.string().c_str();

    PINE_INFO("Date string: {0}, {1}", date_string.size(), date_string);
    PINE_INFO("File path:   {0}", filepath.string());

    const auto open_state = m_camera.open(init_parameters);
    if (open_state != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while opening Zed: {0}",
            sl::toString(open_state).get());
        m_busy_flag = false;
        return;
    }

    const auto recording_state = m_camera.enableRecording(recording_parameters);
    if (recording_state != sl::ERROR_CODE::SUCCESS)
    {
        PINE_WARN("Error while enabling Zed recording: {0}",
            sl::toString(recording_state).get());
        m_busy_flag = false;
        return;
    }

    while (!m_stop_flag)
    {
        const auto grab_state = m_camera.grab(runtime_parameters);
        if (grab_state != sl::ERROR_CODE::SUCCESS)
        {
            PINE_WARN("Error while grabbing Zed data: {0}",
                sl::toString(grab_state).get());
        }
    }

    m_camera.close();
    m_busy_flag = false;
}

CameraManager::CameraManager(const uint16_t port,
    const std::filesystem::path& output_directory)
    : server(port), record_manager(output_directory)
{
}

CameraManager::~CameraManager()
{
    record_manager.stop_record();
    stop_server(server);
}

void CameraManager::run()
{
    server.set_connection_callback(
        [](const pine::ConnectionState& connection) -> bool
        {
            PINE_INFO("New client: {0}", connection.socket.remote_endpoint());
            return true;
        });

    server.set_message_callback(
        [this](const std::vector<uint8_t>& message) -> void
        { on_message(message); });

    PINE_INFO("Server running on {0}", server.acceptor.local_endpoint());
    pine::start_server(server);

    while (running)
    {
        on_update();
    }
}

void CameraManager::on_update()
{
    pine::update_server(server, 10);

    // Get current timestamp
    now = std::chrono::high_resolution_clock::now();

    double elapsed_time =
        std::chrono::duration<double, std::milli>(now - last_frame).count()
        / 1000.0f;

    if (record_manager.is_opened() && streaming && elapsed_time > stream_period)
    {

        auto request = record_manager.get_image(stream_width, stream_height);
        if (request.has_value())
        {
            auto& image = request.value();

            // format message
            zed::ImageMessage message;
            message.topic = "/camera/image";
            message.width = image.specification.width;
            message.height = image.specification.height;
            message.channels = image.specification.channels;
            message.format = image.specification.format;
            message.data = image.buffer;

            for (const auto& client : server.connections)
            {
                send_message(client, message);
            }

            last_frame = std::chrono::high_resolution_clock::now();
        }
    }
}

void CameraManager::on_message(const std::vector<uint8_t>& buffer)
{
    msgpack::object_handle handle =
        msgpack::unpack((char*)buffer.data(), buffer.size());
    msgpack::object object = handle.get();

    try
    {
        auto message = object.as<zed::ControlMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::SettingsMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::SensorMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::StreamMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };
}

void CameraManager::on_message(const zed::ControlMessage& message)
{
    if (message.command == "stop_record")
    {
        record_manager.stop_record();
        auto reply = message;
        reply.topic = "/camera/control_response";
        reply.command = "record_stopped";
        for (const auto& client : server.connections)
        {
            send_message(client, reply);
        }

    }
    else if (message.command == "start_record")
    {
        CameraParameters parameters;
        parameters.resolution = message.resolution;
        parameters.compression = message.compression;
        parameters.fps = message.fps;
        parameters.timeout = message.timeout;
        parameters.enable_image_enhancement = message.enable_image_enhancement;
        parameters.disable_self_calibration = message.disable_self_calibration;
        parameters.require_sensors = message.require_sensors;
        parameters.enable_depth = message.enable_depth;

        record_manager.start_record(parameters);

        auto reply = message;
        reply.topic = "/camera/control_response";
        reply.command = "record_started";
        for (const auto& client : server.connections)
        {
            send_message(client, reply);
        }
    }
}

void CameraManager::on_message(const zed::SettingsMessage& message)
{
    zed::CameraSettings settings;
    settings.brightness = message.brightness;
    settings.contrast = message.contrast;
    settings.hue = message.hue;
    settings.saturation = message.saturation;
    settings.sharpness = message.sharpness;
    settings.gamma = message.gamma;
    settings.gain = message.gain;
    settings.exposure = message.exposure;
    settings.whitebalance = message.whitebalance;
    settings.auto_exposure = message.auto_exposure;
    settings.auto_whitebalance = message.auto_whitebalance;

    const auto success = record_manager.update_settings(settings);
    if (success)
    {
        auto reply = message;
        reply.topic = "/camera/settings_response";

        for (const auto& client : server.connections)
        {
            send_message(client, reply);
        }
    }
}

void CameraManager::on_message(const zed::SensorMessage& message) {}

void CameraManager::on_message(const zed::StreamMessage& message)
{
    if (message.topic == "/desktop/stream_request")
    {
        if (message.command == "stop_stream")
            streaming = false;
        else if (message.command == "start_stream")
            streaming = true;

        stream_width = message.width;
        stream_height = message.height;
        stream_period = message.period;
    }
}

}; // namespace zed

#endif // PINEAPPLE_ENABLE_ZED
