#pragma once

namespace Pineapple::ZED
{

enum class Resolution : uint8_t
{
    HD2K = 1,
    HD1080 = 2,
    HD720 = 3,
    VGA = 4
};

enum class CompressionMode : uint8_t
{
    LOSSLESS = 1,
    H264 = 2,
    H265 = 3
};

struct CameraParameters
{
    // Initialization
    Resolution CameraResolution = Resolution::HD720;
    uint8_t CameraFPS = 0;
    float OpenTimeout = 5.0f;
    bool EnableImageEnhancement = true;
    bool DisableSelfCalibration = false;
    bool RequireSensors = false;

    // Recording
    CompressionMode Compression = CompressionMode::H264;

    // Runtime
    bool EnableDepth = false;
};

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
    int Gamma = 5;
    int Gain = 50;
    int Exposure = 50;
    int Whitebalance = 4000;
    bool AutoExposure = true;
    bool AutoWhitebalance = true;
    bool EnableLED = true;
};

struct ImageConfiguration
{
    uint32_t Width = 1280;
    uint32_t Height = 720;
    View Type = View::LEFT;
};

} // namespace Pineapple::ZED
