#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages/Request.hpp"
#include "Sennet/ZED/Messages/Response.hpp"

namespace Sennet
{

namespace ZED
{

class IdleNode : public Sennet::Node
{
public:
	IdleNode(unsigned short port, uint64_t waitFor = 1, bool verbose = false);
	~IdleNode();

private:
};

}
}
