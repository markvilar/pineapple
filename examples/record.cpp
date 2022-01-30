#include <filesystem>
#include <iostream>
#include <signal.h>

#include <Pine/Pine.hpp>

#include "Pineapple/CameraInterface.hpp"
#include "Pineapple/CameraSettings.hpp"
#include "Pineapple/Messages.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int) { stopFlag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &interrupt_handler);

    Pine::Log::Init();

    Pineapple::ZED::CameraInterface interface("/home/martin/data/debug");

    interface.StartRecord();

    while (!stopFlag)
    {
        auto settingsState = interface.GetCameraSettings();
        auto imuState = interface.GetIMUData();
        auto imageState =
            interface.GetImage(1280, 720, Pineapple::ZED::View::LEFT);

        if (settingsState.has_value())
        {
            const auto settings = settingsState.value();
            PINE_INFO("");
            PINE_INFO("Brightness:        {0}", settings.Brightness);
            PINE_INFO("Contrast:          {0}", settings.Contrast);
            PINE_INFO("Hue:               {0}", settings.Hue);
            PINE_INFO("Saturation:        {0}", settings.Saturation);
            PINE_INFO("Sharpness:         {0}", settings.Sharpness);
            PINE_INFO("Gain:              {0}", settings.Gain);
            PINE_INFO("Exposure:          {0}", settings.Exposure);
            PINE_INFO("Whitebalance:      {0}", settings.Whitebalance);
            PINE_INFO("Auto exposure:     {0}", settings.AutoExposure);
            PINE_INFO("Auto whitebalance: {0}", settings.AutoWhitebalance);
            PINE_INFO("LED status:        {0}", settings.EnableLED);
        }

        if (imuState.has_value())
        {
            const auto imu = imuState.value();
            PINE_INFO("");
            PINE_INFO("IMU acceleration:  {0}, {1}, {2}",
                imu.Acceleration.x,
                imu.Acceleration.y,
                imu.Acceleration.z);
            PINE_INFO("IMU ang. velocity: {0}, {1}, {2}",
                imu.AngularVelocity.x,
                imu.AngularVelocity.y,
                imu.AngularVelocity.z);
        }

        if (imageState.has_value())
        {
            const auto image = imageState.value();
            PINE_INFO("");
            PINE_INFO("Image: {0}, {1}, {2}",
                image.Width,
                image.Height,
                image.Format);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    interface.StopRecord();

    return 0;
}
