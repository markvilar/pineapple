#include "Pineapple/Client.hpp"

namespace Pineapple
{

Client::Client() : Pine::TCPClient<MessageTypes>() {}

Client::~Client() {}

void Client::RequestServerPing()
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::ServerPing;
    std::chrono::system_clock::time_point time =
        std::chrono::system_clock::now();

    message << time;
    Send(message);
}

void Client::RequestSensorControllerInitialization()
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::SensorControllerInitialize;
    Send(message);
}

void Client::RequestSensorControllerShutdown()
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::SensorControllerShutdown;
    Send(message);
}

void Client::RequestSensorControllerStart()
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::SensorControllerStart;
    Send(message);
}

void Client::RequestSensorControllerStop()
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::SensorControllerStop;
    Send(message);
}

void Client::RequestImage(const ZED::View& view)
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::ImageRequest;

    message << view;

    Send(message);
}

void Client::RequestImageStream(const ZED::View& view)
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::ImageStreamRequest;

    message << view;

    Send(message);
}

/*
void Client::RequestInitParametersUpdate(const InitParameters& parameters)
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::InitParametersUpdate;

    message << parameters.depthMode;
    message << parameters.coordinateUnits;
    message << parameters.coordinateSystem;
    message << parameters.enableDepthStabilization;
    message << parameters.minDepth;
    message << parameters.maxDepth;
    message << parameters.enableRightSideDepth;

    message << parameters.resolution;
    message << parameters.flipMode;
    message << parameters.cameraFPS;
    message << parameters.enableImageEnhancement;
    message << parameters.disableSelfCalibration;
    message << parameters.enableVerboseSDK;
    message << parameters.requireSensors;

    Send(message);
}

void Client::RequestRecordingParametersUpdate(
    const RecordingParameters& parameters)
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::RecordingParametersUpdate;

    // TODO: Filename size.
    // message << parameters.filename;
    message << parameters.compressionMode;
    message << parameters.targetBitRate;
    message << parameters.targetFrameRate;

    Send(message);
}

void Client::RequestRuntimeParametersUpdate(const RuntimeParameters& parameters)
{
    Pine::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::RuntimeParametersUpdate;

    message << parameters.sensingMode;
    message << parameters.referenceFrame;
    message << parameters.enableDepth;
    message << parameters.confidenceThreshold;
    message << parameters.textureConfidenceThreshold;

    Send(message);
}
*/

} // namespace Pineapple
