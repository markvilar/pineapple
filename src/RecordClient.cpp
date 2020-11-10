#include "Sennet/ZED/RecordClient.hpp"

namespace Sennet { namespace ZED {

RecordClient::RecordClient()
	: Client<MessageTypes>()
{
}

RecordClient::~RecordClient()
{
}

void RecordClient::PingServer()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerPing;
	std::chrono::system_clock::time_point time =
		std::chrono::system_clock::now();

	message << time;
	Send(message);
}

void RecordClient::SynchronizeServer()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ServerSynchronize;
	Send(message);
}

void RecordClient::InitializeRecorder()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecorderInitialize;
	Send(message);
}

void RecordClient::ShutdownRecorder()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecorderShutdown;
	Send(message);
}

void RecordClient::StartRecord()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::StartRecord;
	Send(message);
}

void RecordClient::StopRecord()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::StopRecord;
	Send(message);
}

void RecordClient::SendInitParameters()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::InitParameters;

	InitParameters parameters;
	message << parameters;
	Send(message);
}

void RecordClient::SendRecordingParameters()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecordingParameters;

	RecordingParameters parameters;
	message << parameters;
	Send(message);
}

void RecordClient::SendRuntimeParameters()
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RuntimeParameters;

	RuntimeParameters parameters;
	message << parameters;
	Send(message);
}

void RecordClient::RequestSettings()
{
}

void RecordClient::RequestImage()
{
}

}}
