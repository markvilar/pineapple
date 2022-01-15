#include "Pineapple/Server.hpp"

namespace Pineapple
{

Server::Server(const uint16_t& port, const std::filesystem::path& dataDirectory)
    : Pine::TCP::Server<MessageTypes>(port), m_CameraInterface(dataDirectory)
{
}

Server::~Server() { Stop(); }

bool Server::OnClientConnect(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client)
{
    m_Clients++;
    Pine::TCP::Message<MessageTypes> message;
    message.Header.ID = MessageTypes::ServerAccept;
    client->Send(message);
    return true;
}

void Server::OnClientDisconnect(Pine::Ref<Pine::TCP::Connection<MessageTypes>>)
{
    m_Clients--;
}

void Server::OnMessage(Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    // Dispatch the message to the right function based on the header ID.
    switch (message.Header.ID)
    {
    case MessageTypes::ServerPing:
        OnServerPingRequest(client, message);
        break;

    // Sensor controls.
    case MessageTypes::SensorControllerInitialize:
        OnSensorControllerInitializationRequest(client, message);
        break;
    case MessageTypes::SensorControllerShutdown:
        OnSensorControllerShutdownRequest(client, message);
        break;
    case MessageTypes::SensorControllerStart:
        OnSensorControllerStartRequest(client, message);
        break;
    case MessageTypes::SensorControllerStop:
        OnSensorControllerStopRequest(client, message);
        break;
    case MessageTypes::ImageRequest:
        OnImageRequest(client, message);
        break;
    case MessageTypes::ImageStreamRequest:
        OnImageStreamRequest(client, message);
        break;

    // Parameter updates.
    case MessageTypes::InitParametersUpdate:
        OnInitParametersUpdate(client, message);
        break;
    case MessageTypes::RecordingParametersUpdate:
        OnRecordingParametersUpdate(client, message);
        break;
    case MessageTypes::RuntimeParametersUpdate:
        OnRuntimeParametersUpdate(client, message);
        break;
    }
}

void Server::OnServerPingRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message) const
{
    PINE_INFO("[{0}] Ping Request.", client->GetID());
    client->Send(message);
}

void Server::OnSensorControllerInitializationRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Initialization Request.", client->GetID());
    if (!m_CameraInterface.IsRunning())
    {
        m_CameraInterface.Initialize();
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerAccept;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerDeny;
        client->Send(message);
    }
    */
}

void Server::OnSensorControllerShutdownRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Shutdown Request.", client->GetID());
    if (m_CameraInterface.IsRunning())
    {
        m_CameraInterface.Shutdown();
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerAccept;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerDeny;
        client->Send(message);
    }
    */
}

void Server::OnSensorControllerStartRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Start Record Request.", client->GetID());
    if (!m_CameraInterface.IsRecording())
    {
        m_CameraInterface.Start();
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerAccept;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerDeny;
        client->Send(message);
    }
    */
}

void Server::OnSensorControllerStopRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Stop Record Request.", client->GetID());
    if (m_CameraInterface.IsRecording())
    {
        m_CameraInterface.Stop();
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerAccept;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerDeny;
        client->Send(message);
    }
    */
}

void Server::OnImageRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Image Request.", client->GetID());
    if (m_CameraInterface.IsCameraOpen())
    {
        auto view = ZED::View::Left;
        message >> view;

        auto image = m_CameraInterface.GetImage(view);
        uint32_t width = image->GetWidth();
        uint32_t height = image->GetHeight();
        uint32_t channels = image->GetChannels();
        auto data = image->GetBuffer();

        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::Image;
        message << data;
        message << width << height << channels;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::SensorControllerDeny;
        client->Send(message);
    }
    */
}

void Server::OnImageStreamRequest(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Image Stream Request.", client->GetID());
    if (m_CameraInterface.IsCameraOpen())
    {
        ZED::View view = ZED::View::Left;
        message >> view;

        auto image = m_CameraInterface.GetImage(view);
        uint32_t width = image->GetWidth();
        uint32_t height = image->GetHeight();
        uint32_t channels = image->GetChannels();
        auto data = image->GetBuffer();

        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::ImageStream;
        message << data;
        message << width << height << channels;
        client->Send(message);
    }
    else
    {
        Pine::TCP::Message<MessageTypes> message;
        message.Header.ID = MessageTypes::ImageStreamDeny;
        client->Send(message);
    }
    */
}

void Server::OnInitParametersUpdate(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Initialization Parameters Request.", client->GetID());
    InitParameters parameters;

    message >> parameters.requireSensors;
    message >> parameters.enableVerboseSDK;
    message >> parameters.disableSelfCalibration;
    message >> parameters.enableImageEnhancement;
    message >> parameters.cameraFPS;
    message >> parameters.flipMode;
    message >> parameters.resolution;

    message >> parameters.enableRightSideDepth;
    message >> parameters.maxDepth;
    message >> parameters.minDepth;
    message >> parameters.enableDepthStabilization;
    message >> parameters.coordinateSystem;
    message >> parameters.coordinateUnits;
    message >> parameters.depthMode;

    m_CameraInterface.SetInitParameters(parameters);
    */
}

void Server::OnRecordingParametersUpdate(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Recording Parameters Request.", client->GetID());
    RecordingParameters parameters;

    message >> parameters.targetFrameRate;
    message >> parameters.targetBitRate;
    message >> parameters.compressionMode;
    // TODO: Fix filename size in message.
    // message >> parameters.filename;

    m_CameraInterface.SetRecordingParameters(parameters);
    */
}

void Server::OnRuntimeParametersUpdate(
    Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
    Pine::TCP::Message<MessageTypes>& message)
{
    /*
    PINE_INFO("[{0}] Runtime Parameters Request.", client->GetID());
    RuntimeParameters parameters;

    message >> parameters.textureConfidenceThreshold;
    message >> parameters.confidenceThreshold;
    message >> parameters.enableDepth;
    message >> parameters.referenceFrame;
    message >> parameters.sensingMode;

    m_CameraInterface.SetRuntimeParameters(parameters);
    */
}

} // namespace Pineapple
