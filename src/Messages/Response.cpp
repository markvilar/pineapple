#include <SennetZED/Messages/Response.hpp>

namespace Sennet
{

namespace ZED
{

StateResponse::StateResponse(const std::string address, 
	const unsigned int port,
	const RecorderState state,
	const InitParameters initParameters,
	const RecordingParameters recordingParameters,
	const RuntimeParameters runtimeParameters,
	const Image image,
	const std::vector<std::pair<std::string, int>> settings)
	: Response(address, port), m_InitParameters(initParameters),
	m_RecordingParameters(recordingParameters), 
	m_RuntimeParameters(runtimeParameters),
	m_Image(image),
	m_Settings(settings)
{
}

}
}
