#include "Sennet-ZED/Client.hpp"

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

void Client::RequestImage(const View& view)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ImageRequest;

	message << view;

	Send(message);
}

void Client::RequestImageStream(const View& view)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::ImageStreamRequest;

	message << view;

	Send(message);
}

void Client::RequestInitParametersUpdate(
	const InitParameters& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::InitParametersUpdate;

	message << parameters.depthMode;
	message << parameters.coordinateUnits;
	message << parameters.coordinateSystem;
	message << parameters.enableDepthStabilization;
	message << parameters.minDepth;
	message << parameters.maxDepth;
	message << parameters.enableRightSideDepth;

	message << parameters.resolution;
	message << parameters.flipMode;
	message << parameters.cameraFPS;
	message << parameters.enableImageEnhancement;
	message << parameters.disableSelfCalibration;
	message << parameters.enableVerboseSDK;
	message << parameters.requireSensors;

	Send(message);
}

void Client::RequestRecordingParametersUpdate(
	const RecordingParameters& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RecordingParametersUpdate;
	
	// TODO: Filename size.
	// message << parameters.filename;
	message << parameters.compressionMode;
	message << parameters.targetBitRate;
	message << parameters.targetFrameRate;

	Send(message);
}

void Client::RequestRuntimeParametersUpdate(
	const RuntimeParameters& parameters)
{
	Message<MessageTypes> message;
	message.Header.ID = MessageTypes::RuntimeParametersUpdate;
	
	message << parameters.sensingMode;
	message << parameters.referenceFrame;
	message << parameters.enableDepth;
	message << parameters.confidenceThreshold;
	message << parameters.textureConfidenceThreshold;

	Send(message);
}

}}
