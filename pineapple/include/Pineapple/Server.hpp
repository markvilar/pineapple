#pragma once
#include "Pine/Pine.hpp"

#include <filesystem>

#include "Pineapple/CameraInterface.hpp"
#include "Pineapple/Messages.hpp"

namespace Pineapple
{

class Server : public Pine::TCP::Server<MessageTypes>
{
public:
    Server(const uint16_t& port, const std::filesystem::path& dataDirectory);
    virtual ~Server();

protected:
    virtual bool OnClientConnect(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client) override;

    virtual void OnClientDisconnect(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>>) override;

    virtual void OnMessage(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message) override;

private:
    void OnServerPingRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message) const;

    // Sensor control requests.
    void OnSensorControllerInitializationRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnSensorControllerShutdownRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnSensorControllerStartRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnSensorControllerStopRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);

    // Image and image stream requests.
    void OnImageRequest(Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnImageStreamRequest(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);

    // Parameter update requests.
    void OnInitParametersUpdate(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnRecordingParametersUpdate(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);
    void OnRuntimeParametersUpdate(
        Pine::Ref<Pine::TCP::Connection<MessageTypes>> client,
        Pine::TCP::Message<MessageTypes>& message);

private:
    ZED::CameraInterface m_CameraInterface;
    uint8_t m_Clients = 0;
};

} // namespace Pineapple
