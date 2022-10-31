#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include <msgpack.hpp>

#include <pine/pine.hpp>

#include "pineapple/zed/types.hpp"

namespace zed
{

struct ControlMessage
{
    std::string topic;

    std::string command;
    uint8_t resolution = 0;
    uint8_t compression = 0;
    uint8_t fps = 0;
    float timeout = 5.0f;
    bool enable_image_enhancement = true;
    bool disable_self_calibration = false;
    bool require_sensors = false;
    bool enable_depth = false;

    MSGPACK_DEFINE(topic, command, resolution, compression, fps, timeout,
        enable_image_enhancement, disable_self_calibration, require_sensors,
        enable_depth);
};

struct SettingsMessage
{
    std::string topic;

    int brightness{};
    int contrast{};
    int hue{};
    int saturation{};
    int sharpness{};
    int gamma{};
    int gain{};
    int exposure{};
    int whitebalance{};
    bool auto_exposure{};
    bool auto_whitebalance{};

    MSGPACK_DEFINE(topic, brightness, contrast, hue, saturation, sharpness,
        gamma, gain, exposure, whitebalance, auto_exposure, auto_whitebalance);
};

struct SensorMessage
{
    std::string topic{};

    float acceleration_x;
    float acceleration_y;
    float acceleration_z;
    float turnrate_x;
    float turnrate_y;
    float turnrate_z;

    MSGPACK_DEFINE(acceleration_x, acceleration_y, acceleration_z, turnrate_x,
        turnrate_y, turnrate_z);
};

struct StreamMessage
{
    std::string topic{};

    std::string command;
    uint16_t width = 0;
    uint16_t height = 0;
    float period = 1;

    MSGPACK_DEFINE(topic, command, width, height, period);
};

struct ImageMessage
{
    std::string topic{};

    uint16_t width{};
    uint16_t height{};
    uint16_t channels{};
    std::string format{};
    std::vector<uint8_t> data{};

    MSGPACK_DEFINE(topic, width, height, channels, format, data);
};

} // namespace zed
