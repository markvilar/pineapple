#include "Sennet/ZED/RecorderNode.hpp"

#include "Sennet/ZED/Layers/NetworkLayer.hpp"
#include "Sennet/ZED/Layers/SensorLayer.hpp"

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
