#pragma once

#include "Sennet/Sennet.hpp"

#include "Sennet-ZED/Messages.hpp"
#include "Sennet-ZED/InitParameters.hpp"
#include "Sennet-ZED/RecordingParameters.hpp"
#include "Sennet-ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class Client : public Sennet::Client<MessageTypes>
{
public:
	Client();
	virtual ~Client();

	void RequestServerPing();
	void RequestServerSynchronization();
	
	void RequestSensorControllerInitialization();
	void RequestSensorControllerShutdown();
	void RequestSensorControllerStart();
	void RequestSensorControllerStop();

	void RequestInitParametersUpdate(
		const InitParameters& parameters);
	void RequestRecordingParametersUpdate(
		const RecordingParameters& parameters);
	void RequestRuntimeParametersUpdate(
		const RuntimeParameters& parameters);

	void RequestSettings();
	void RequestImage();
	void RequestImageStream();

private:

};

}}
