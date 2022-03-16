#pragma once

namespace Pineapple
{

enum class MessageTypes : uint32_t
{
    Ping,

    SensorRequest,
    SensorResponse,

    ImageRequest,
    ImageResponse,
};

} // namespace Pineapple
