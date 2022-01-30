#pragma once

namespace Pineapple::ZED
{

enum class FlipMode : uint8_t
{
    OFF = 1,
    ON = 2,
    AUTO = 3
};

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
    FlipMode CameraFlip = FlipMode::OFF;
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

} // namespace Pineapple::ZED
