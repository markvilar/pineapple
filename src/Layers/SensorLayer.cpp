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
	SN_TRACE("[SensorLayer] Got message!");
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
	SN_TRACE("[SensorLayer] Dispatched to OnCommandRequest!");
	auto command = msg->GetCommand();
	switch (command)
	{
		case Sennet::ZED::Command::None:
			SN_TRACE("[SensorLayer] Command: None.");
			break;
		case Sennet::ZED::Command::Initialize:
			SN_TRACE("[SensorLayer] Command: Initialize.");
			m_Recorder->Initialize();
			break;
		case Sennet::ZED::Command::Shutdown:
			SN_TRACE("[SensorLayer] Command: Shutdown.");
			m_Recorder->Shutdown();
			break;
		case Sennet::ZED::Command::StartRecord:
			SN_TRACE("[SensorLayer] Command: Start Record.");
			m_Recorder->StartRecord();
			break;
		case Sennet::ZED::Command::StopRecord:
			SN_TRACE("[SensorLayer] Command: Stop Record.");
			m_Recorder->StopRecord();
			break;
	}
	return true; // Blocks further propagation.
}

bool SensorLayer::OnSettingsRequest(Sennet::Ref<SettingsRequest> msg)
{
	SN_TRACE("[SensorLayer] Dispatched to OnSettingsRequest!");
	return true; // Blocks further propagation.
}

bool SensorLayer::OnStateRequest(Sennet::Ref<StateRequest> msg)
{
	SN_TRACE("[SensorLayer] Dispatched to OnStateRequest!");
	return true; // Blocks further propagation.
}

}
}
