#include "Sennet/ZED/RecordServer.hpp"

namespace Sennet { namespace ZED {

RecordServer::RecordServer(const uint16_t& port, const std::string& root)
	: ::Sennet::Server<MessageTypes>(port), m_Recorder(root)
{
}

RecordServer::~RecordServer()
{
	m_Recorder.Shutdown();
}

bool RecordServer::OnClientConnect(
	Sennet::Ref<Sennet::Connection<MessageTypes>> client)
{
	m_Clients++;
	return true;
}

void RecordServer::OnClientDisconnect(
	Sennet::Ref<Sennet::Connection<MessageTypes>>) 
{
	m_Clients--;
	if (m_Clients == 0)
	{
		m_Recorder.Shutdown();
	}
}

void RecordServer::OnMessage(
	Sennet::Ref<Sennet::Connection<MessageTypes>> client,
	Sennet::Message<MessageTypes>& message) 
{
	switch (message.Header.ID)
	{
	case MessageTypes::ServerPing:
		SN_INFO("[{0}] Server Ping.", client->GetID());
		client->Send(message);
		break;
	case MessageTypes::RecorderInitialize:
		// TODO: Add feedback.
		SN_INFO("[{0}] Recorder Initialize.", client->GetID());
		m_Recorder.Initialize();
		break;
	case MessageTypes::RecorderShutdown:
		SN_INFO("[{0}] Recorder Shutdown.", client->GetID());
		m_Recorder.Shutdown();
		break;
	case MessageTypes::StartRecord:
		SN_INFO("[{0}] Recorder Start Record.", client->GetID());
		m_Recorder.StartRecord();
		break;
	case MessageTypes::StopRecord:
		SN_INFO("[{0}] Recorder Stop Record.", client->GetID());
		m_Recorder.StartRecord();
		break;
	}
}


}}
