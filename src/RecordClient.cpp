#include "Sennet/ZED/RecordClient.hpp"

namespace Sennet { namespace ZED {

RecordClient::RecordClient()
	: Client<MessageTypes>()
{
}

RecordClient::~RecordClient()
{
}

void RecordClient::RequestServerPing()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerPing;
	std::chrono::system_clock::time_point time =
		std::chrono::system_clock::now();

	message << time;
	Send(message);
}

void RecordClient::RequestServerSynchronization()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerSynchronize;
	Send(message);
}

void RecordClient::RequestRecorderInitialization()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecorderInitialize;
	Send(message);
}

void RecordClient::RequestRecorderShutdown()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecorderShutdown;
	Send(message);
}

void RecordClient::RequestStartRecord()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::StartRecord;
	Send(message);
}

void RecordClient::RequestStopRecord()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::StopRecord;
	Send(message);
}

void RecordClient::RequestInitParametersUpdate(
	const Ref<InitParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::InitParametersUpdate;

	message << *parameters;
	Send(message);
}

void RecordClient::RequestRecordingParametersUpdate(
	const Ref<RecordingParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecordingParametersUpdate;

	message << *parameters;
	Send(message);
}

void RecordClient::RequestRuntimeParametersUpdate(
	const Ref<RuntimeParameters>& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RuntimeParametersUpdate;

	message << *parameters;
	Send(message);
}

void RecordClient::RequestSettings()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::SettingsRequest;
	Send(message);
}

void RecordClient::RequestImage()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ImageRequest;
	Send(message);
}

}}
