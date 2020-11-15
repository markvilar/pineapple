#include "Sennet/ZED/Client.hpp"

namespace Sennet { namespace ZED {

Client::Client()
	: Sennet::Client<MessageTypes>()
{
}

Client::~Client()
{
}

void Client::RequestServerPing()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerPing;
	std::chrono::system_clock::time_point time =
		std::chrono::system_clock::now();

	message << time;
	Send(message);
}

void Client::RequestServerSynchronization()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerSynchronize;
	Send(message);
}

void Client::RequestSensorControllerInitialization()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SensorControllerInitialize;
	Send(message);
}

void Client::RequestSensorControllerShutdown()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SensorControllerShutdown;
	Send(message);
}

void Client::RequestSensorControllerStart()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SensorControllerStart;
	Send(message);
}

void Client::RequestSensorControllerStop()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SensorControllerStop;
	Send(message);
}

void Client::RequestInitParametersUpdate(
	const Ref<InitParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::InitParametersUpdate;

	message << *parameters;
	Send(message);
}

void Client::RequestRecordingParametersUpdate(
	const Ref<RecordingParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecordingParametersUpdate;

	message << *parameters;
	Send(message);
}

void Client::RequestRuntimeParametersUpdate(
	const Ref<RuntimeParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RuntimeParametersUpdate;

	message << *parameters;
	Send(message);
}

void Client::RequestSettings()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SettingsRequest;
	Send(message);
}

void Client::RequestImage()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ImageRequest;
	Send(message);
}

void Client::RequestImageStream()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ImageStreamRequest;
	Send(message);
}

}}
