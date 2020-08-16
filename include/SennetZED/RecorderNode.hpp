#pragma once
#include <Sennet/Sennet.hpp>

#include <SennetZED/Messages/Request.hpp>
#include <SennetZED/Messages/Response.hpp>

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
