#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/Recorder.hpp"

#include "Sennet/ZED/InitParameters.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class RecordServer : public ::Sennet::Server<MessageTypes>
{
public:
	RecordServer(const uint16_t& port, const std::string& root);
	virtual ~RecordServer();

protected:
	virtual bool OnClientConnect(
		Sennet::Ref<Sennet::Connection<MessageTypes>> client)
		override;

	virtual void OnClientDisconnect(
		Sennet::Ref<Sennet::Connection<MessageTypes>>) 
		override;

	virtual void OnMessage(
		Sennet::Ref<Sennet::Connection<MessageTypes>> client,
		Sennet::Message<MessageTypes>& message) 
		override;


private:
	Recorder m_Recorder;
	uint8_t m_Clients = 0;
};

}}
