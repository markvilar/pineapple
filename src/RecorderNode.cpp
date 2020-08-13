#include <SennetZED/RecorderNode.hpp>

#include <SennetZED/Layers/NetworkLayer.hpp>
#include <SennetZED/Layers/SensorLayer.hpp>

namespace Sennet
{

namespace ZED
{

RecorderNode::RecorderNode(unsigned short port, uint64_t waitFor=1)	
{
	PushLayer(new NetworkLayer(port, waitFor));
	PushLayer(new SensorLayer());
}

RecorderNode::~RecorderNode()
{
}

}
}
