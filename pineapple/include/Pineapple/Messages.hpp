#pragma once

namespace Pineapple
{

enum class MessageTypes : uint32_t
{
    ServerPing = 0,
    ServerSynchronize = 1,
    ServerAccept = 2,
    ServerDeny = 3,

    SensorControllerInitialize = 11,
    SensorControllerShutdown = 12,
    SensorControllerStart = 13,
    SensorControllerStop = 14,
    SensorControllerAccept = 15,
    SensorControllerDeny = 16,

    ImageRequest = 20,
    Image = 21,
    ImageDeny = 22,
    ImageStreamRequest = 23,
    ImageStream = 24,
    ImageStreamDeny = 25,

    InitParametersUpdate = 30,
    InitParametersAccept = 32,
    InitParametersDeny = 33,

    RecordingParametersUpdate = 40,
    RecordingParametersAccept = 43,
    RecordingParametersDeny = 44,

    RuntimeParametersUpdate = 50,
    RuntimeParametersAccept = 53,
    RuntimeParametersDeny = 54,

    VideoSettingsRequest = 60,
    VideoSettings = 61,
};

} // namespace Pineapple
