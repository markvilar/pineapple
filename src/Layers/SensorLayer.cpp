#include <SennetZED/Layers/SensorLayer.hpp>

namespace Sennet
{

namespace ZED
{

SensorLayer::SensorLayer()
	: Layer("Sensor")
{
	m_Recorder.reset(new Recorder());
}

SensorLayer::~SensorLayer()
{
}

void SensorLayer::OnAttach()
{
}

void SensorLayer::OnDetach()
{
}

void SensorLayer::OnUpdate(Sennet::Timestep ts)
{
}

void SensorLayer::OnMessage(Sennet::Ref<Sennet::Message> msg)
{
	Sennet::MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<Sennet::ZED::CommandRequest>(
		std::bind(&SensorLayer::OnCommandRequest, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ZED::SettingsRequest>(
		std::bind(&SensorLayer::OnSettingsRequest, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<Sennet::ZED::StateRequest>(
		std::bind(&SensorLayer::OnStateRequest, this, 
		std::placeholders::_1));
}

bool SensorLayer::OnCommandRequest(Sennet::Ref<CommandRequest> msg)
{
	auto command = msg->GetCommand();
	switch (command)
	{
		case Sennet::ZED::Command::None:
			SN_TRACE("SensorLayer got command: None.");
			break;
		case Sennet::ZED::Command::Initialize:
			SN_TRACE("SensorLayer got command: Initialize.");
			m_Recorder->Initialize();
			break;
		case Sennet::ZED::Command::Shutdown:
			SN_TRACE("SensorLayer got command: Shutdown.");
			m_Recorder->Shutdown();
			break;
		case Sennet::ZED::Command::StartRecord:
			SN_TRACE("SensorLayer got command: Start Record.");
			m_Recorder->StartRecord();
			break;
		case Sennet::ZED::Command::StopRecord:
			SN_TRACE("SensorLayer got command: Stop Record.");
			m_Recorder->StopRecord();
			break;
	}
	return true; // Blocks further propagation.
}

bool SensorLayer::OnSettingsRequest(Sennet::Ref<SettingsRequest> msg)
{
	auto initParameters = msg->GetInitParameters();
	auto recordingParameters = msg->GetRecordingParameters();
	auto runtimeParameters = msg->GetRuntimeParameters();
	m_Recorder->SetParametersCache(initParameters, recordingParameters,
		runtimeParameters);
	return true; // Blocks further propagation.
}

bool SensorLayer::OnStateRequest(Sennet::Ref<StateRequest> msg)
{
	auto remoteEndpoint = msg->GetSender();
	SubmitStateResponse(remoteEndpoint.first, remoteEndpoint.second);
	return true;
}

void SensorLayer::SubmitStateResponse(const std::string address, 
	const unsigned short port)
{
	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (!connectionManager)
	{
		SN_WARN("Connection manager not initialized.");
		return;
	}

	auto connection = connectionManager->FindConnection(address, port);
	if (!connection)
	{
		SN_WARN("Connection with remote endpoint {0}:{1} not found.",
			address, port);
		return;
	}

	Sennet::Ref<Sennet::Image> image = nullptr;
	std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
		parameters;
	if (m_Recorder->IsCameraOpened())
	{
		image = m_Recorder->GetImage();
		parameters = m_Recorder->GetParameters();
	}
	else
	{
		image.reset(new Sennet::Image());
		parameters = m_Recorder->GetParametersCache();
	}
	
	auto state = m_Recorder->GetState();

	// TODO: Get settings.
	std::vector<std::pair<std::string, int>> settings;
	
	auto msg = Sennet::CreateRef<StateResponse>(
		connection->GetLocalInformation().first,
		connection->GetLocalInformation().second,
		state,
		std::get<0>(parameters),
		std::get<1>(parameters),
		std::get<2>(parameters),
		*image,
		settings);

	connectionManager->SubmitMessage(connection, msg);
}

}
}
