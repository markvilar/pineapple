#pragma once

#include <cstdint>

#include <pine/pine.hpp>

namespace zed
{

enum class CameraAction : uint8_t
{
    UNKNOWN = 0,
    START_RECORD = 1,
    STOP_RECORD = 2
};

enum class CameraResponse : uint8_t
{
    UNKNOWN = 0,
    CONTROL_SUCCESS = 1,
    CONTROL_FAILURE = 2
};

enum class Resolution : uint8_t
{
    HD2K = 1,
    HD1080 = 2,
    HD720 = 3,
    VGA = 4
};

enum class Compression : uint8_t
{
    LOSSLESS = 1,
    H264 = 2,
    H265 = 3,
    H264_LOSSLESS = 4,
    H265_LOSSLESS = 5
};

enum class View : uint8_t
{
    LEFT = 1,
    RIGHT = 2,
    LEFT_GRAY = 3,
    RIGHT_GRAY = 4,
    SIDE_BY_SIDE = 5,
};

inline uint8_t view_channels(const View view)
{
    return [view]()
    {
        switch (view)
        {
        case View::LEFT:
            return 4;
        case View::RIGHT:
            return 4;
        case View::LEFT_GRAY:
            return 1;
        case View::RIGHT_GRAY:
            return 1;
        case View::SIDE_BY_SIDE:
            return 4;
        default:
            return 0;
        }
    }();
}

struct CameraParameters
{
    Resolution resolution = Resolution::HD720;
    Compression compression = Compression::H264;
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
    bool enable_led = false;
};

inline bool operator==(const CameraSettings& lhs, const CameraSettings& rhs)
{
    return lhs.brightness == rhs.brightness 
        && lhs.contrast == rhs.contrast
        && lhs.hue == rhs.hue
        && lhs.saturation == rhs.saturation
        && lhs.sharpness == rhs.sharpness
        && lhs.gamma == rhs.gamma
        && lhs.gain == rhs.gain
        && lhs.exposure == rhs.exposure
        && lhs.whitebalance == rhs.whitebalance
        && lhs.auto_exposure == rhs.auto_exposure
        && lhs.auto_whitebalance == rhs.auto_whitebalance
        && lhs.enable_led == rhs.enable_led;
}

inline bool operator!=(const CameraSettings& lhs, const CameraSettings& rhs)
{
    return !(lhs == rhs);
}

struct ImageSpecification
{
    uint32_t width = 1280;
    uint32_t height = 720;
    View view = View::LEFT;

public:
    ImageSpecification() = default;

    ImageSpecification(const uint32_t width, const uint32_t height,
        const View view)
        : width(width), height(height), view(view)
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
        const View view)
        : specification(width, height, view)
    {
        const auto channels = [view]()
        {
            switch (view)
            {
            case View::LEFT:
                return 4;
            case View::RIGHT:
                return 4;
            case View::LEFT_GRAY:
                return 1;
            case View::RIGHT_GRAY:
                return 1;
            case View::SIDE_BY_SIDE:
                return 4;
            default:
                return 0;
            }
        }();
        buffer = std::vector<uint8_t>(data, data + width * height * channels);
    }
};

struct CameraState
{
    bool opened;
    bool recording;
    bool stopped;
};

struct MemoryState
{
    uint64_t total_space;
    uint64_t free_space;
    uint64_t available_space;
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
