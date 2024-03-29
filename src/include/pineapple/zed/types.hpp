#pragma once

#include <cstdint>

#include <pine/pine.hpp>

namespace zed
{

enum Resolution : uint8_t
{
    HD2K = 1,
    HD1080 = 2,
    HD720 = 3,
    VGA = 4
};

enum Compression : uint8_t
{
    LOSSLESS = 1,
    H264 = 2,
    H265 = 3,
    H264_LOSSLESS = 4,
    H265_LOSSLESS = 5
};

enum View : uint8_t
{
    LEFT = 1,
    RIGHT = 2,
    LEFT_GRAY = 3,
    RIGHT_GRAY = 4,
    SIDE_BY_SIDE = 5,
};

struct CameraParameters
{
    uint8_t resolution = Resolution::HD720;
    uint8_t compression = Compression::H264;
    uint8_t fps = 0;
    float timeout = 5.0f;
    bool enable_image_enhancement = true;
    bool disable_self_calibration = false;
    bool require_sensors = false;
    bool enable_depth = false;
};

struct CameraSettings
{
    int brightness = 4;
    int contrast = 4;
    int hue = 0;
    int saturation = 4;
    int sharpness = 4;
    int gamma = 5;
    int gain = 50;
    int exposure = 50;
    int whitebalance = 4000;
    bool auto_exposure = true;
    bool auto_whitebalance = true;
};

inline bool operator==(const CameraSettings& lhs, const CameraSettings& rhs)
{
    return lhs.brightness == rhs.brightness && lhs.contrast == rhs.contrast
        && lhs.hue == rhs.hue && lhs.saturation == rhs.saturation
        && lhs.sharpness == rhs.sharpness && lhs.gamma == rhs.gamma
        && lhs.gain == rhs.gain && lhs.exposure == rhs.exposure
        && lhs.whitebalance == rhs.whitebalance
        && lhs.auto_exposure == rhs.auto_exposure
        && lhs.auto_whitebalance == rhs.auto_whitebalance;
}

inline bool operator!=(const CameraSettings& lhs, const CameraSettings& rhs)
{
    return !(lhs == rhs);
}

struct ImageSpecification
{
    uint16_t width = 1280;
    uint16_t height = 720;
    uint16_t channels = 4;
    std::string format{"BGRA"};

public:
    ImageSpecification() = default;

    ImageSpecification(const uint16_t width_, const uint16_t height_,
        const uint16_t channels_)
        : width(width_), height(height_), channels(channels_)
    {
    }
};

struct Image
{
    ImageSpecification specification{};
    std::vector<uint8_t> buffer{};

public:
    Image() = default;

    Image(const uint8_t* data, const uint32_t width, const uint32_t height,
        uint16_t channels)
        : specification(width, height, channels)
    {
        buffer = std::vector<uint8_t>(data, data + width * height * channels);
    }
};

struct SensorData
{
    float pressure;
    float temperature_left;
    float temperature_right;
    pine::Vec3 acceleration{0.0f};
    pine::Vec3 turnrate{0.0f};
};

}; // namespace zed
