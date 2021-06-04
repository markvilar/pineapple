#pragma once

#include "Sennet/Sennet.hpp"

#include "Sennet-ZED/Messages.hpp"
#include "Sennet-ZED/InitParameters.hpp"
#include "Sennet-ZED/RecordingParameters.hpp"
#include "Sennet-ZED/RuntimeParameters.hpp"
#include "Sennet-ZED/Settings.hpp"

namespace Sennet { namespace ZED {

class Client : public Sennet::Client<MessageTypes>
{
public:
	Client();
	virtual ~Client();

	void RequestServerPing();
	
	void RequestSensorControllerInitialization();
	void RequestSensorControllerShutdown();
	void RequestSensorControllerStart();
	void RequestSensorControllerStop();

	void RequestImage(const View& view);
	void RequestImageStream(const View& view);

	void RequestInitParametersUpdate(const InitParameters& parameters);
	void RequestRecordingParametersUpdate(const RecordingParameters& parameters);
	void RequestRuntimeParametersUpdate(const RuntimeParameters& parameters);

private:

};

}}
