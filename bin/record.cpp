#include <filesystem>
#include <signal.h>

#include <pine/pine.hpp>

#include "pineapple/zed/camera_manager.hpp"
#include "pineapple/zed/types.hpp"

sig_atomic_t stop_flag = 0;

void interrupt_handler(int) { stop_flag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &interrupt_handler);

    pine::Log::init();

    zed::RecordManager manager("/home/martin/data");

    zed::CameraParameters parameters;
    parameters.resolution = zed::Resolution::HD1080;
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
        auto settings_request = manager.get_settings();

        PINE_INFO("Camera opened:    {0}", manager.is_opened());
        PINE_INFO("Camera recording: {0}", manager.is_recording());

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
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    manager.stop_record();

    return 0;
}
