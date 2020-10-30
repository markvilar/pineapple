#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages/Request.hpp"
#include "Sennet/ZED/Messages/Response.hpp"

namespace Sennet
{

namespace ZED
{

class RecorderNode : public Sennet::Node
{
public:
	RecorderNode(unsigned short port, uint64_t waitFor, bool verbose);
	~RecorderNode();

private:
};

}
}
