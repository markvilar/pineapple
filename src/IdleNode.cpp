#include <SennetZED/IdleNode.hpp>

#include <SennetZED/Layers/NetworkLayer.hpp>

namespace Sennet
{

namespace ZED
{

IdleNode::IdleNode(unsigned short port, uint64_t waitFor, bool verbose)	
	: Sennet::Node(verbose)
{
	PushLayer(new NetworkLayer(port, waitFor));
}

IdleNode::~IdleNode()
{
}

}
}
