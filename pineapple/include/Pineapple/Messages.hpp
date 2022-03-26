#pragma once

#include <cstdint>
#include <cstring>

#include "Pineapple/CameraControls.hpp"
#include "Pineapple/SensorData.hpp"

namespace Pineapple
{

enum class MessageType: uint8_t
{
    CameraStartRequest,
    CameraStopRequest,
    CameraStatusRequest,
    CameraStatusResponse,

    ImageRequest,
    ImageResponse,

    CameraSettingsRequest,
    CameraSettingsResponse,

    SensorDataRequest,
    SensorDataResponse,
};

struct CameraStartRequest
{
    const MessageType Type = MessageType::CameraStartRequest;
    ZED::CameraParameters Parameters;
};

struct CameraStopRequest
{
    const MessageType Type = MessageType::CameraStopRequest;
};

struct CameraStatusRequest
{
    const MessageType Type = MessageType::CameraStatusRequest;
};

struct CameraStatusResponse
{
    const MessageType Type = MessageType::CameraStatusResponse;
    ZED::CameraState Status;
    ZED::CameraSettings Settings;
};

struct ImageRequest
{
    const MessageType Type = MessageType::ImageRequest;
    ZED::ImageConfiguration Configuration;
};

struct ImageResponse
{
    const MessageType Type = MessageType::ImageResponse;
    Pine::Image Image;
};

// FIXME: Does not work for structs due to padding
template <typename T>
Pine::Message FormatMessage(const T& data)
{
    static_assert(std::is_standard_layout<T>::value,
        "Data is too complex to be pushed into vector.");
    Pine::Message message;
    message.Body.resize(sizeof(T));
    std::memcpy(message.Body.data(), &data, sizeof(T));
    message.Header.Size = message.Body.size();
    return message;
}

}; // namespace Pineapple
