#include "Sennet/ZED/RecordServer.hpp"

namespace Sennet { namespace ZED {

RecordServer::RecordServer(const uint16_t& port, const std::string& root)
	: Server<MessageTypes>(port), m_Recorder(root)
{
}

RecordServer::~RecordServer()
{
	m_Recorder.Shutdown();
}

bool RecordServer::OnClientConnect(Ref<Connection<MessageTypes>> client)
{
	m_Clients++;
	return true;
}

void RecordServer::OnClientDisconnect(Ref<Connection<MessageTypes>>)
{
	m_Clients--;
	if (m_Clients == 0)
	{
		m_Recorder.Shutdown();
	}
}

void RecordServer::OnMessage(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) 
{
	switch (message.Header.ID)
	{
	case MessageTypes::ServerPing:
		SN_INFO("[{0}] Server Ping.", client->GetID());
		client->Send(message);
		break;
	case MessageTypes::ServerSynchronize:
		SN_INFO("[{0}] Server Synchronize.", client->GetID());
		break;
	case MessageTypes::RecorderInitialize:
		SN_INFO("[{0}] Recorder Initialize.", client->GetID());
		//m_Recorder.Initialize();
		break;
	case MessageTypes::RecorderShutdown:
		SN_INFO("[{0}] Recorder Shutdown.", client->GetID());
		//m_Recorder.Shutdown();
		break;
	case MessageTypes::StartRecord:
		SN_INFO("[{0}] Recorder Start Record.", client->GetID());
		//m_Recorder.StartRecord();
		break;
	case MessageTypes::StopRecord:
		SN_INFO("[{0}] Recorder Stop Record.", client->GetID());
		//m_Recorder.StartRecord();
		break;
	case MessageTypes::InitParameters:
		SN_INFO("[{0}] Initialization Parameters.", client->GetID());
		break;
	case MessageTypes::RecordingParameters:
		SN_INFO("[{0}] Recording Parameters.", client->GetID());
		break;
	case MessageTypes::RuntimeParameters:
		SN_INFO("[{0}] Runtime Parameters.", client->GetID());
		break;
	}
}

}}
