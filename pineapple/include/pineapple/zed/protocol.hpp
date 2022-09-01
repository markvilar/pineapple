#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include <pine/pine.hpp>

#include "pineapple/message.hpp"
#include "pineapple/zed/types.hpp"

namespace pineapple::zed
{

enum class ServiceIdentifier : uint8_t
{
    UNKNOWN = 0,

    CONTROL_REQUEST = 1,
    CONTROL_RESPONSE = 2,

    SETTINGS_REQUEST = 3,
    SETTINGS_RESPONSE = 4,

    MEMORY_REQUEST = 5,
    MEMORY_RESPONSE = 6,

    SENSOR_REQUEST = 7,
    SENSOR_RESPONSE = 8,

    IMAGE_REQUEST = 9,
    IMAGE_RESPONSE = 10
};

// ----------------------------------------------------------------------------
// Control service
// ----------------------------------------------------------------------------

struct ControlService
{
    struct RequestData
    {
        CameraAction action = CameraAction::UNKNOWN;

        Resolution resolution = Resolution::HD720;
        Compression compression = Compression::H264;
        uint8_t fps = 0;
        float timeout = 5.0f;
        bool enable_image_enhancement = true;
        bool disable_self_calibration = false;
        bool require_sensors = false;
        bool enable_depth = false;
    };

    struct ResponseData
    {
        CameraResponse action_response = CameraResponse::UNKNOWN;

        Resolution resolution = Resolution::HD720;
        Compression compression = Compression::H264;
        uint8_t fps = 0;
        float timeout = 5.0f;
        bool enable_image_enhancement = true;
        bool disable_self_calibration = false;
        bool require_sensors = false;
        bool enable_depth = false;
    };

    using Request = Message<ServiceIdentifier, RequestData>;
    using Response = Message<ServiceIdentifier, ResponseData>;
};

// ----------------------------------------------------------------------------
// Image service
// ----------------------------------------------------------------------------

struct ImageService
{
    struct RequestData
    {
        uint32_t width = 1280;
        uint32_t height = 720;
        View view = View::LEFT;
    };

    struct ResponseData
    {
        uint32_t width = 1280;
        uint32_t height = 720;
        View view = View::LEFT;
        std::vector<uint8_t> buffer{};
    };

    using Request = Message<ServiceIdentifier, RequestData>;
    using Response = Message<ServiceIdentifier, ResponseData>;
};

// ----------------------------------------------------------------------------
// Memory Service
// ----------------------------------------------------------------------------

struct MemoryService
{
    struct RequestData
    {
    };

    struct ResponseData
    {
        uint64_t total_space{0};
        uint64_t free_space{0};
        uint64_t available_space{0};
    };

    using Request = Message<ServiceIdentifier, RequestData>;
    using Response = Message<ServiceIdentifier, ResponseData>;
};

// ----------------------------------------------------------------------------
// Sensor service
// ----------------------------------------------------------------------------

struct SensorService
{
    struct RequestData
    {
    };

    struct ResponseData
    {
        float pressure;
        float temperature_left;
        float temperature_right;
        pine::Vec3 acceleration{0.0f};
        pine::Vec3 turnrate{0.0f};
    };

    using Request = Message<ServiceIdentifier, RequestData>;
    using Response = Message<ServiceIdentifier, ResponseData>;
};

// ----------------------------------------------------------------------------
// Settings service
// ----------------------------------------------------------------------------

struct SettingsService
{
    struct RequestData
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
        bool enable_led = true;
    };

    struct ResponseData
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
        bool enable_led = true;
    };

    using Request = Message<ServiceIdentifier, RequestData>;
    using Response = Message<ServiceIdentifier, ResponseData>;
};

// ----------------------------------------------------------------------------
// Service data serialization
// ----------------------------------------------------------------------------

template <typename Archive>
void serialize(Archive& archive, ControlService::RequestData& request)
{
    archive(request.action,
        request.resolution,
        request.compression,
        request.fps,
        request.timeout,
        request.enable_image_enhancement,
        request.disable_self_calibration,
        request.require_sensors,
        request.enable_depth);
}

template <typename Archive>
void serialize(Archive& archive, ControlService::ResponseData& response)
{
    archive(response.action_response,
        response.resolution,
        response.compression,
        response.fps,
        response.timeout,
        response.enable_image_enhancement,
        response.disable_self_calibration,
        response.require_sensors,
        response.enable_depth);
}

template <typename Archive>
void serialize(Archive& archive, ImageService::RequestData& request)
{
    archive(request.width, request.height, request.view);
}

template <typename Archive>
void serialize(Archive& archive, ImageService::ResponseData& response)
{
    archive(response.width, response.height, response.view, response.buffer);
}

template <typename Archive>
void serialize(Archive& archive, MemoryService::RequestData& request)
{
}

template <typename Archive>
void serialize(Archive& archive, MemoryService::ResponseData& response)
{
    archive(response.total_space,
        response.free_space,
        response.available_space);
}

template <typename Archive>
void serialize(Archive& archive, SensorService::RequestData& request)
{
}

template <typename Archive>
void serialize(Archive& archive, SensorService::ResponseData& response)
{
    archive(response.pressure,
        response.temperature_left,
        response.temperature_right,
        response.acceleration,
        response.turnrate);
}

template <typename Archive>
void serialize(Archive& archive, SettingsService::RequestData& request)
{
    archive(request.brightness,
        request.contrast,
        request.hue,
        request.saturation,
        request.sharpness,
        request.gamma,
        request.gain,
        request.exposure,
        request.whitebalance,
        request.auto_exposure,
        request.auto_whitebalance,
        request.enable_led);
}

template <typename Archive>
void serialize(Archive& archive, SettingsService::ResponseData& response)
{
    archive(response.brightness,
        response.contrast,
        response.hue,
        response.saturation,
        response.sharpness,
        response.gamma,
        response.gain,
        response.exposure,
        response.whitebalance,
        response.auto_exposure,
        response.auto_whitebalance,
        response.enable_led);
}

} // namespace pineapple::zed
