#pragma once
#include "Sennet/Sennet.hpp"

namespace Sennet { namespace ZED {

enum class MessageTypes: uint32_t
{
	ServerPing			= 0,
	ServerSynchronize		= 1,
	ServerAccept			= 2,
	ServerDeny			= 3,

	SensorControllerInitialize	= 11,
	SensorControllerShutdown	= 12,
	SensorControllerStart		= 13,
	SensorControllerStop		= 14,
	SensorControllerAccept		= 15,
	SensorControllerDeny		= 16,

	InitParametersUpdate		= 20,
	RecordingParametersUpdate	= 21,
	RuntimeParametersUpdate		= 22,
	ParametersAccept		= 23,
	ParametersDeny			= 24,

	SettingsRequest			= 30,
	Settings			= 31,
	SettingsDeny			= 32,

	ImageRequest			= 40,
	Image				= 41,
	ImageDeny			= 42,
};

}}
