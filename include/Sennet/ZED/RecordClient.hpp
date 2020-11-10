#pragma once

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/InitParameters.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class RecordClient : public Sennet::Client<MessageTypes>
{
public:
	RecordClient();
	virtual ~RecordClient();

	void RequestServerPing();
	void RequestServerSynchronization();
	
	void RequestRecorderInitialization();
	void RequestRecorderShutdown();
	void RequestStartRecord();
	void RequestStopRecord();

	void RequestInitParametersUpdate(
		const Ref<InitParameters>& parameters);
	void RequestRecordingParametersUpdate(
		const Ref<RecordingParameters>& parameters);
	void RequestRuntimeParametersUpdate(
		const Ref<RuntimeParameters>& parameters);

	void RequestSettings();
	void RequestImage();

private:

};

}}
