#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "Pineapple/Zed/Types.hpp"

namespace Pineapple::Zed 
{

enum class MessageIdentifier : uint8_t
{
    Unknown = 0,
    ControlRequest = 1,
    ControlResponse = 2,
    SettingsRequest = 3,
    SettingsResponse = 4,
    StateRequest = 5,
    StateResponse = 6,
    SensorRequest = 7,
    SensorResponse = 8,
    ImageRequest = 9,
    ImageResponse = 10
};

// ----------------------------------------------------------------------------
// ControlRequest
// ----------------------------------------------------------------------------

struct ControlRequest
{
    CameraAction action = CameraAction::UNKNOWN;
    CameraParameters parameters{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::ControlRequest;
    }
};

template <typename Archive>
void serialize(Archive& archive, ControlRequest& request)
{
    archive(request.action, request.parameters);
}

// ----------------------------------------------------------------------------
// ControlResponse
// ----------------------------------------------------------------------------

struct ControlResponse
{
    CameraResponse response = CameraResponse::UNKNOWN;

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::ControlResponse;
    }
};

template <typename Archive>
void serialize(Archive& archive, ControlResponse& response)
{
    archive(response.response);
}

// ----------------------------------------------------------------------------
// SettingsRequest
// ----------------------------------------------------------------------------


struct SettingsRequest
{
    CameraSettings settings{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::SettingsRequest;
    }
};

template <typename Archive>
void serialize(Archive& archive, SettingsRequest& request)
{
    archive(request.settings);
}

// ----------------------------------------------------------------------------
// SettingsResponse
// ----------------------------------------------------------------------------

struct SettingsResponse
{
    CameraSettings settings{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::SettingsResponse;
    }
};

template <typename Archive>
void serialize(Archive& archive, SettingsResponse& response)
{
    archive(response.settings);
}

// ----------------------------------------------------------------------------
// StateRequest
// ----------------------------------------------------------------------------

struct StateRequest
{
    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::StateRequest;
    }
};

template <typename Archive>
void serialize(Archive& archive, StateRequest& request)
{
}

// ----------------------------------------------------------------------------
// StateResponse
// ----------------------------------------------------------------------------

struct StateResponse
{
    CameraState camera_state{};
    MemoryState memory_state{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::StateResponse;
    }
};

template <typename Archive>
void serialize(Archive& archive, StateResponse& response)
{
    archive(response.camera_state, response.memory_state);
}

// ----------------------------------------------------------------------------
// SensorRequest
// ----------------------------------------------------------------------------

struct SensorRequest
{
    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::SensorRequest;
    }
};

template <typename Archive>
void serialize(Archive& archive, SensorRequest& request)
{
}

// ----------------------------------------------------------------------------
// SensorResponse
// ----------------------------------------------------------------------------

struct SensorResponse
{
    SensorData sensor_data{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::SensorResponse;
    }
};

template <typename Archive>
void serialize(Archive& archive, SensorResponse& response)
{
    archive(response.sensor_data);
}

// ----------------------------------------------------------------------------
// ImageRequest
// ----------------------------------------------------------------------------

struct ImageRequest
{
    ImageSpecification image_specs{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::ImageRequest;
    }
};

template <typename Archive>
void serialize(Archive& archive, ImageRequest& request)
{
    archive(request.image_specs);
}

// ----------------------------------------------------------------------------
// ImageResponse
// ----------------------------------------------------------------------------

struct ImageResponse
{
    Image image{};

    static constexpr MessageIdentifier GetStaticIdentifier()
    {
        return MessageIdentifier::ImageResponse;
    }
}; 

template <typename Archive>
void serialize(Archive& archive, ImageResponse& response)
{
    archive(response.image);
}

} // namespace Pineapple::Zed
