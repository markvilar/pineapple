#include <SennetZED/RecorderNode.hpp>

#include <SennetZED/Layers/NetworkLayer.hpp>
#include <SennetZED/Layers/SensorLayer.hpp>

namespace Sennet
{

namespace ZED
{

RecorderNode::RecorderNode(unsigned short port, uint64_t waitFor, bool verbose)
	: Sennet::Node(verbose)
{
	PushLayer(new NetworkLayer(port, waitFor));
	PushLayer(new SensorLayer());
}

RecorderNode::~RecorderNode()
{
}

}
}
