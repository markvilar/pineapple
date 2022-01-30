#pragma once

namespace Pineapple::ZED
{

enum class Settings : uint8_t
{
    Brightness = 1,
    Contrast = 2,
    Hue = 3,
    Saturation = 4,
    Sharpness = 5,
    Gain = 6,
    Exposure = 7,
    AECAGC = 8,
    WhitebalanceTemperature = 9,
    WhitebalanceAuto = 10,
    LEDStatus = 11,
};

enum class View : uint8_t
{
    Left = 1,
    Right = 2,
    LeftGray = 3,
    RightGray = 4,
    LeftUnrectified = 5,
    RightUnrectified = 6,
    LeftUnrectifiedGray = 7,
    RightUnrectifiedGray = 8,
    SideBySide = 9,
};

struct CameraSettings
{
    int Brightness = 4;
    int Contrast = 4;
    int Hue = 4;
    int Saturation = 4;
    int Sharpness = 4;
    int Gain = 50;
    int Exposure = 50;
    int Whitebalance = 4000;
    bool AutoExposure = true;
    bool AutoWhitebalance = true;
    bool EnableLED = true;
};

} // namespace Pineapple::ZED
