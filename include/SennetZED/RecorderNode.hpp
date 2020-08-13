#pragma once
#include <Sennet/Sennet.hpp>

namespace Sennet
{

namespace ZED
{

class RecorderNode : public ::Sennet::Node
{
public:
	RecorderNode(unsigned short port, uint64_t waitFor);
	~RecorderNode();

private:
};

}
}
