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

	void PingServer();
	void SynchronizeServer();
	
	void InitializeRecorder();
	void ShutdownRecorder();
	void StartRecord();
	void StopRecord();

	void SendInitParameters();
	void SendRecordingParameters();
	void SendRuntimeParameters();

	void RequestSettings();
	void RequestImage();

private:

};

}}
