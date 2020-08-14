#include <SennetZED/Messages/Response.hpp>

namespace Sennet
{

namespace ZED
{

StateResponse::StateResponse(const std::string address, 
	const unsigned int port,
	const InitParameters initParameters,
	const RecordingParameters recordingParameters,
	const RuntimeParameters runtimeParameters,
	const Image& image)
	: Response(address, port), m_InitParameters(initParameters),
	m_RecordingParameters(recordingParameters), 
	m_RuntimeParameters(runtimeParameters),
	m_Image(image)
{
}

}
}
