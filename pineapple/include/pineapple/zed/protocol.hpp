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

struct ControlRequest
{
    std::string topic;
    std::string action;
    uint8_t fps = 0;
    float timeout = 5.0f;
    bool enable_image_enhancement = true;
    bool disable_self_calibration = false;
    bool require_sensors = false;
    bool enable_depth = false;

public:
    MSGPACK_DEFINE(topic,
        action, 
        fps,
        timeout,
        enable_image_enhancement,
        disable_self_calibration,
        require_sensors,
        enable_depth);
};

struct ControlResponse
{
    std::string topic;
    std::string response;
    uint8_t fps = 0;
    float timeout = 5.0f;
    bool enable_image_enhancement = true;
    bool disable_self_calibration = false;
    bool require_sensors = false;
    bool enable_depth = false;

public:
    MSGPACK_DEFINE(topic,
        response, 
        fps,
        timeout,
        enable_image_enhancement,
        disable_self_calibration,
        require_sensors,
        enable_depth);
};

} // namespace zed
