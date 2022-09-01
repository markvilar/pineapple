#include "pineapple/zed/camera_manager.hpp"

#include "pineapple/utils.hpp"
#include "pineapple/serialization.hpp"
#include "pineapple/zed/protocol.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace pineapple::zed
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

std::optional<CameraSettings> RecordManager::request_camera_settings()
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
    settings.enable_led =
        m_camera.getCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS);

    return settings;
}

std::optional<SensorData> RecordManager::request_sensor_data()
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

    pineapple::zed::SensorData data;
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

std::optional<Image> RecordManager::request_image(const uint32_t width,
    const uint32_t height, const View view)
{
    if (!is_opened())
    {
        return {};
    }

    const auto native_view = [view]()
    {
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
    m_camera.retrieveImage(native_image,
        native_view,
        sl::MEM::CPU,
        sl::Resolution(width, height));

    Image image(native_image.getPtr<uint8_t>(),
        native_image.getWidth(),
        native_image.getHeight(),
        view);

    return std::move(image);
}

bool RecordManager::update_camera_settings(const CameraSettings& settings)
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
    m_camera.setCameraSettings(sl::VIDEO_SETTINGS::LED_STATUS,
        settings.enable_led);
    return true;
}

void RecordManager::record_worker(const RecordJob job)
{
    auto [init_parameters, recording_parameters, runtime_parameters] =
        to_stereolabs(job.parameters);

    const auto date_string = current_date_time() + ".svo";
    const auto filepath = job.output_directory / date_string;
    recording_parameters.video_filename = filepath.string().c_str();

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
    : m_server(port), m_record_manager(output_directory)
{
}

CameraManager::~CameraManager()
{
    PINE_INFO("Stopping server.");
    stop_server(m_server);
}

void CameraManager::run()
{
    pine::start_server(m_server,
        [this](const pine::ConnectionState& connection) -> bool
        {
            PINE_INFO("Server got connection: {0}",
                connection.socket.remote_endpoint());
            return true;
        });

    while (m_running)
    {
        on_update();
    }
}

void CameraManager::on_update()
{
    pine::update_server(m_server,
        [this](const std::vector<uint8_t>& message) -> void
        { on_message(message); });
}

void CameraManager::on_message(const std::vector<uint8_t>& buffer)
{
    PINE_INFO("Camera manager: Got message: Size = {0}", buffer.size());
    pineapple::MemoryViewInputArchive input_archive(buffer.data(), 
        buffer.size());

    ServiceIdentifier identifier;
    input_archive.deserialize(identifier);

    if (identifier == ServiceIdentifier::UNKNOWN)
    {
        PINE_INFO("Camera manager: Unknown message.");
    }
    else if(identifier == ServiceIdentifier::CONTROL_REQUEST)
    {
        zed::ControlService::Request::DataType request;
        input_archive.deserialize(request); // TODO: Catch error
        on_request(request);
    }
    else if (identifier == ServiceIdentifier::IMAGE_REQUEST)
    {
        zed::ImageService::Request::DataType request;
        input_archive.deserialize(request); // TODO: Catch error
        on_request(request);
    }
    else if (identifier == ServiceIdentifier::MEMORY_REQUEST)
    {
        zed::MemoryService::Request::DataType request;
        input_archive.deserialize(request); // TODO: Catch error
        on_request(request);
    }
    else if (identifier == ServiceIdentifier::SENSOR_REQUEST)
    {
        zed::SensorService::Request::DataType request;
        input_archive.deserialize(request); // TODO: Catch error
        on_request(request);
    }
    else if (identifier == ServiceIdentifier::SETTINGS_REQUEST)
    {
        zed::SettingsService::Request::DataType request;
        input_archive.deserialize(request); // TODO: Catch error
        on_request(request);
    }
    else
    {
        PINE_INFO("Camera manager: Not handling message.");
    }
}

void CameraManager::on_request(
    const zed::ControlService::Request::DataType& request)
{
    PINE_INFO("Camera manager: Got control request.");
    PINE_INFO(" - Action:          {0}", request.action);
    PINE_INFO(" - Compression:     {0}", request.compression);
    PINE_INFO(" - FPS:             {0}", request.fps);
    PINE_INFO(" - Timeout:         {0}", request.timeout);
    PINE_INFO(" - Image enhance.:  {0}", request.enable_image_enhancement);
    PINE_INFO(" - Self calib.:     {0}", request.disable_self_calibration);
    PINE_INFO(" - Req. sensors:    {0}", request.require_sensors);
    PINE_INFO(" - Enable depth:    {0}", request.enable_depth);
}

void CameraManager::on_request(
    const zed::ImageService::Request::DataType& request)
{
    PINE_INFO("Camera manager: Got image request.");
    PINE_INFO(" - Width:  {0}", request.width);
    PINE_INFO(" - Height: {0}", request.height);
    PINE_INFO(" - View:   {0}", request.view);
}

void CameraManager::on_request(
    const zed::MemoryService::Request::DataType& request)
{
    PINE_INFO("Camera manager: Got memory request.");
}

void CameraManager::on_request(
    const zed::SensorService::Request::DataType& request)
{
    PINE_INFO("Camera manager: Got sensor request.");
}

void CameraManager::on_request(
    const zed::SettingsService::Request::DataType& request)
{
    PINE_INFO("Camera manager: Got settings request.");
    PINE_INFO(" - Brightness:   {0}", request.brightness);
    PINE_INFO(" - Contrast:     {0}", request.contrast);
    PINE_INFO(" - Hue:          {0}", request.hue);
    PINE_INFO(" - Saturation:   {0}", request.saturation);
    PINE_INFO(" - Sharpness:    {0}", request.sharpness);
    PINE_INFO(" - Gamma:        {0}", request.gamma);
    PINE_INFO(" - Gain:         {0}", request.gain);
    PINE_INFO(" - Exposure:     {0}", request.exposure);
    PINE_INFO(" - Whitebalance: {0}", request.whitebalance);
    PINE_INFO(" - Auto expo.:   {0}", request.auto_exposure);
    PINE_INFO(" - Auto white.:  {0}", request.auto_whitebalance);
    PINE_INFO(" - Enable LED:   {0}", request.enable_led);
}

}; // namespace pineapple::zed

#endif // PINEAPPLE_ENABLE_ZED
