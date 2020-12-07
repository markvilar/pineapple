#include "Sennet/ZED/Server.hpp"

namespace Sennet { namespace ZED {

Server::Server(const uint16_t& port, const std::string& root)
	: Sennet::Server<MessageTypes>(port), m_SensorController(root)
{
}

Server::~Server()
{
	Stop();
}

bool Server::OnClientConnect(Ref<Connection<MessageTypes>> client)
{
	m_Clients++;
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerAccept;
	client->Send(message);
	return true;
}

void Server::OnClientDisconnect(Ref<Connection<MessageTypes>>)
{
	m_Clients--;
}

void Server::OnMessage(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) 
{
	// Dispatch the message to the right function based on the header ID.
	switch (message.Header.ID)
	{
	case MessageTypes::ServerPing:
		OnServerPingRequest(client, message);
		break;
	case MessageTypes::ServerSynchronize:
		OnServerSynchronizationRequest(client, message);
		break;
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
	case MessageTypes::ImageStreamRequest:
		OnImageStreamRequest(client, message);
		break;
	}
}

void Server::OnServerPingRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) const
{
	SN_INFO("[{0}] Ping Request.", client->GetID());
	client->Send(message);
}

void Server::OnServerSynchronizationRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message) const
{
	SN_INFO("[{0}] Synchronization Request.", client->GetID());
	Message<MessageTypes> reply;
	reply.Header.ID = MessageTypes::ServerSynchronize;
	Timestamp ts;
	ts.Grab();
	reply << ts.GetMilliseconds();
	client->Send(reply);
}

void Server::OnSensorControllerInitializationRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Initialization Request.", client->GetID());
	if (!m_SensorController.IsRunning())
	{
		m_SensorController.Initialize();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

void Server::OnSensorControllerShutdownRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Shutdown Request.", client->GetID());
	if (m_SensorController.IsRunning())
	{
		m_SensorController.Shutdown();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

void Server::OnSensorControllerStartRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Start Record Request.", client->GetID());
	if (!m_SensorController.IsRecording())
	{
		m_SensorController.Start();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

void Server::OnSensorControllerStopRequest(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Stop Record Request.", client->GetID());
	if (m_SensorController.IsRecording())
	{
		m_SensorController.Stop();
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerAccept;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

void Server::OnInitParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Initialization Parameters Request.", client->GetID());
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

	m_SensorController.SetInitParameters(parameters);
}

void Server::OnRecordingParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Recording Parameters Request.", client->GetID());
	RecordingParameters parameters;
	
	message >> parameters.targetFrameRate;
	message >> parameters.targetBitRate;
	message >> parameters.compressionMode;
	message >> parameters.filename;

	m_SensorController.SetRecordingParameters(parameters);
}

void Server::OnRuntimeParametersUpdate(
	Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Runtime Parameters Request.", client->GetID());
	RuntimeParameters parameters;

	message >> parameters.textureConfidenceThreshold;
	message >> parameters.confidenceThreshold;
	message >> parameters.enableDepth;
	message >> parameters.referenceFrame;
	message >> parameters.sensingMode;

	m_SensorController.SetRuntimeParameters(parameters);
}

void Server::OnSettingsRequest(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Settings Request.", client->GetID());
}

void Server::OnImageRequest(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Image Request.", client->GetID());
	if (m_SensorController.IsCameraOpen())
	{
		auto image = m_SensorController.GetImage();
		uint32_t width = image->GetWidth();
		uint32_t height = image->GetHeight();
		uint32_t channels = image->GetChannels();
		auto data = image->GetBuffer();

		SN_CORE_INFO("Image: {0} ({1}, {2}, {3})", image->GetSize(),
			width, height, channels);

		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::Image;
		message << data;
		message << width << height << channels;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

void Server::OnImageStreamRequest(Ref<Connection<MessageTypes>> client,
	Message<MessageTypes>& message)
{
	SN_INFO("[{0}] Image Stream Request.", client->GetID());
	if (m_SensorController.IsCameraOpen())
	{
		auto image = m_SensorController.GetImage();
		uint32_t width = image->GetWidth();
		uint32_t height = image->GetHeight();
		uint32_t channels = image->GetChannels();
		auto data = image->GetBuffer();

		SN_CORE_INFO("Image: {0} ({1}, {2}, {3})", image->GetSize(),
			width, height, channels);

		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::ImageStream;
		message << data;
		message << width << height << channels;
		client->Send(message);
	}
	else
	{
		Message<MessageTypes> message;
		message.Header.ID = MessageTypes::SensorControllerDeny;
		client->Send(message);
	}
}

}}
