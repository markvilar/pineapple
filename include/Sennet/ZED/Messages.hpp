#pragma once
#include "Sennet/Sennet.hpp"

namespace Sennet { namespace ZED {

enum class MessageTypes: uint32_t
{
	ServerAccept		= 0,
	ServerDeny		= 1,
	ServerPing		= 2,
	ServerSynchronize	= 3,

	RecorderInitialize	= 11,
	RecorderShutdown	= 12,
	StartRecord		= 13,
	StopRecord		= 14,
	RecorderActionAccept	= 15,
	RecorderActionDeny	= 16,

	InitParameters		= 15,
	RecordingParameters	= 16,
	RuntimeParameters	= 17,
	ServerParametersAccept	= 18,
	ServerParametersDeny	= 19,

	RequestSettings		= 20,
	Settings		= 21,

	RequestImage		= 22,
	Image			= 23,
};

}}
