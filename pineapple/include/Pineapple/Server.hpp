#pragma once

#include <filesystem>

#include <Pine/Pine.hpp>

#include "Pineapple/CameraInterface.hpp"
#include "Pineapple/Messages.hpp"

namespace Pineapple
{

class Server : public Pine::TCPServer<MessageTypes>
{
public:
    Server(const uint16_t& port, const std::filesystem::path& dataDirectory);
    virtual ~Server();

protected:
    virtual bool OnClientConnect(
        Pine::Ref<Pine::Connection<MessageTypes>> client) override;

    virtual void OnClientDisconnect(
        Pine::Ref<Pine::Connection<MessageTypes>>) override;

    virtual void OnMessage(Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message) override;

private:
    void OnServerPingRequest(Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message) const;

    // Sensor control requests.
    void OnSensorControllerInitializationRequest(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnSensorControllerShutdownRequest(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnSensorControllerStartRequest(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnSensorControllerStopRequest(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);

    // Image and image stream requests.
    void OnImageRequest(Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnImageStreamRequest(Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);

    // Parameter update requests.
    void OnInitParametersUpdate(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnRecordingParametersUpdate(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);
    void OnRuntimeParametersUpdate(
        Pine::Ref<Pine::Connection<MessageTypes>> client,
        Pine::Message<MessageTypes>& message);

private:
    ZED::CameraInterface m_CameraInterface;
    uint8_t m_Clients = 0;
};

} // namespace Pineapple
