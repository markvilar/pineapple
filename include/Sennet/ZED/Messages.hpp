#pragma once
#include "Sennet/Sennet.hpp"

namespace Sennet { namespace ZED {

enum class MessageTypes: uint32_t
{
	ServerAccept			= 0,
	ServerDeny			= 1,
	ServerPing			= 2,
	ServerSynchronize		= 3,

	RecorderInitialize		= 11,
	RecorderShutdown		= 12,
	StartRecord			= 13,
	StopRecord			= 14,
	RecorderActionAccept		= 15,
	RecorderActionDeny		= 16,

	InitParametersUpdate		= 17,
	RecordingParametersUpdate	= 18,
	RuntimeParametersUpdate		= 19,
	ParametersUpdateAccept		= 20,
	ParametersUpdateDeny		= 21,

	RequestSettings			= 22,
	Settings			= 23,

	RequestImage			= 24,
	Image				= 25,
};

}}
