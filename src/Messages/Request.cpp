#include <SennetZED/Messages/Request.hpp>

namespace Sennet
{

namespace ZED
{

SettingsRequest::SettingsRequest(const std::string address, 
	const unsigned int port,
	const InitParameters& initParameters,
	const RecordingParameters& recordingParameters,
	const RuntimeParameters& runtimeParameters)
	: Request(address, port), m_InitParameters(initParameters),
	m_RecordingParameters(recordingParameters),
	m_RuntimeParameters(runtimeParameters)
{
}

}
}
