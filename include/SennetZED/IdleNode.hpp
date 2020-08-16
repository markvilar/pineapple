#pragma once
#include <Sennet/Sennet.hpp>

#include <SennetZED/Messages/Request.hpp>
#include <SennetZED/Messages/Response.hpp>

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
