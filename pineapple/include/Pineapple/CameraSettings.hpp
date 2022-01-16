#pragma once

namespace Pineapple::ZED
{

enum class View : uint8_t
{
    LEFT = 1,
    RIGHT = 2,
    LEFT_GRAY = 3,
    RIGHT_GRAY = 4,
    SIDE_BY_SIDE = 5,
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
