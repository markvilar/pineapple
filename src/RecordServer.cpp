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
	// Dispatch the message to the right function based on the header ID.
	switch (message.Header.ID)
	{
	case MessageTypes::ServerPing:
		OnPingRequest(client, message);
		break;
	case MessageTypes::ServerSynchronize:
		OnSynchronizationRequest(client, message);
		break;
	case MessageTypes::RecorderInitialize:
		OnInitializationRequest(client, message);
		break;
	case MessageTypes::RecorderShutdown:
		OnShutdownRequest(client, message);
		break;
	case MessageTypes::StartRecord:
		OnStartRecordRequest(client, message);
		break;
	case MessageTypes::StopRecord:
		OnStopRecordRequest(client, message);
		break;
	case MessageTypes::InitParametersUpdate:
		OnInitParametersUpdate(client, message);
		break;
	case MessageTypes::RecordingParametersUpdate:
		OnRecordingParametersUpdate(client, message);
		break;
	case MessageTypes::RuntimeParametersUpdate:
		OnRuntimeParametersUpdate(client, message);
		break;
	case MessageTypes::SettingsRequest:
		OnSettingsRequest(client, message);
		break;
	case MessageTypes::ImageRequest:
		OnImageRequest(client, message);
		break;
	}
}

void RecordServer::OnPingRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) const
{
	SN_INFO("[{0}] Ping Request.", client->GetID());
	client->Send(message);
}

void RecordServer::OnSynchronizationRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) const
{
	SN_INFO("[{0}] Synchronization Request.", client->GetID());
}

void RecordServer::OnInitializationRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Initialization Request.", client->GetID());
	if (!m_Recorder.IsRunning())
	{
		m_Recorder.Initialize();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionDeny;
		client->Send(message);
	}
}

void RecordServer::OnShutdownRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Shutdown Request.", client->GetID());
	if (m_Recorder.IsRunning())
	{
		m_Recorder.Shutdown();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionDeny;
		client->Send(message);
	}
}

void RecordServer::OnStartRecordRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Start Record Request.", client->GetID());
	if (!m_Recorder.IsRecording())
	{
		m_Recorder.StartRecord();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionDeny;
		client->Send(message);
	}
}

void RecordServer::OnStopRecordRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Stop Record Request.", client->GetID());
	if (m_Recorder.IsRecording())
	{
		m_Recorder.StopRecord();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::RecorderActionDeny;
		client->Send(message);
	}
}

void RecordServer::OnInitParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Initialization Parameters Request.", client->GetID());
}

void RecordServer::OnRecordingParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Recording Parameters Request.", client->GetID());
}

void RecordServer::OnRuntimeParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Runtime Parameters Request.", client->GetID());
}

void RecordServer::OnSettingsRequest(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Settings Request.", client->GetID());
}

void RecordServer::OnImageRequest(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Image Request.", client->GetID());
	if (m_Recorder.IsCameraOpen())
	{
		/*
		auto image = m_Recorder.GetImage();
		uint32_t width = image->GetWidth();
		uint32_t height = image->GetHeight();
		uint32_t channels = image->GetChannels();
		auto data = image->GetBuffer();

		SN_CORE_INFO("Image: {0} ({1}, {2}, {3})", data.size(),
			width, height, channels);

		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::Image;
		message << data;
		message << width << height << channels;
		SN_CORE_INFO("Message size: {0}, Buffer Size: {1}", 
			message.Size(), data.size());
		client->Send(message);
		*/
	}
}

}}
