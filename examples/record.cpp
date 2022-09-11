#include <filesystem>
#include <iostream>
#include <signal.h>

#include <pine/pine.hpp>

#include "pineapple/zed/camera_manager.hpp"
#include "pineapple/zed/types.hpp"

sig_atomic_t stop_flag = 0;

void InterruptHandler(int) { stop_flag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &InterruptHandler);

    pine::Log::init();

    zed::RecordManager manager();

    zed::CameraParameters parameters;
    parameters.resolution = zed::Resolution::HD2K;
    parameters.compression = zed::Compression::H264;
    parameters.fps = 0;
    parameters.timeout = 5.0f;
    parameters.enable_image_enhancement = true;
    parameters.disable_self_calibration = false;
    parameters.require_sensors = false;
    parameters.enable_depth = false;

    manager.start_record(parameters);

    while (!stop_flag)
    {
        auto settings_request = manager.request_camera_settings();
        auto sensor_request = manager.request_sensor_data();
        auto image_request = manager.request_image(1280, 720, zed::View::LEFT);

        if (settings_request.has_value())
        {
            const auto settings = settings_request.value();
            PINE_INFO("");
            PINE_INFO("Brightness:        {0}", settings.brightness);
            PINE_INFO("Contrast:          {0}", settings.contrast);
            PINE_INFO("Hue:               {0}", settings.hue);
            PINE_INFO("Saturation:        {0}", settings.saturation);
            PINE_INFO("Sharpness:         {0}", settings.sharpness);
            PINE_INFO("Gain:              {0}", settings.gain);
            PINE_INFO("Exposure:          {0}", settings.exposure);
            PINE_INFO("Whitebalance:      {0}", settings.whitebalance);
            PINE_INFO("Auto exposure:     {0}", settings.auto_exposure);
            PINE_INFO("Auto whitebalance: {0}", settings.auto_whitebalance);
            PINE_INFO("LED status:        {0}", settings.enable_led);
        }

        if (sensor_request.has_value())
        {
            const auto sensor = sensor_request.value();
            PINE_INFO("");
            PINE_INFO("IMU acceleration:  {0}, {1}, {2}",
                sensor.acceleration.x,
                sensor.acceleration.y,
                sensor.acceleration.z);
            PINE_INFO("IMU ang. velocity: {0}, {1}, {2}",
                sensor.turnrate.x,
                sensor.turnrate.y,
                sensor.turnrate.z);
        }

        if (image_request.has_value())
        {
            const auto image = image_request.value();
            PINE_INFO("");
            PINE_INFO("Image: {0}, {1}, {2}",
                image.specification.width,
                image.specification.height,
                image.specification.view);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    manager.stop_record();

    return 0;
}
