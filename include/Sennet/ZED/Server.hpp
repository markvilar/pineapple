#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/SensorController.hpp"

#include "Sennet/ZED/InitParameters.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class Server : public Sennet::Server<MessageTypes>
{
public:
	Server(const uint16_t& port, const std::string& root);
	virtual ~Server();

protected:
	virtual bool OnClientConnect(Ref<Connection<MessageTypes>> client)
		override;

	virtual void OnClientDisconnect(Ref<Connection<MessageTypes>>)
		override;

	virtual void OnMessage(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message) override;

private:
	void OnServerPingRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message) const;

	void OnServerSynchronizationRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message) const;

	void OnSensorControllerInitializationRequest(
		Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnSensorControllerShutdownRequest(
		Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnSensorControllerStartRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnSensorControllerStopRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnInitParametersUpdate(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnRecordingParametersUpdate(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnRuntimeParametersUpdate(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnSettingsRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);

	void OnImageRequest(Ref<Connection<MessageTypes>> client,
		Message<MessageTypes>& message);
		
private:
	SensorController m_SensorController;
	uint8_t m_Clients = 0;
};

}}
