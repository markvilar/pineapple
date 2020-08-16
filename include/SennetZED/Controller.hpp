#pragma once
#include <Sennet/Sennet.hpp>

namespace Sennet
{

namespace ZED
{

class Controller : public Sennet::Application
{
public:
	Controller(unsigned short port, uint64_t waitFor, bool verbose);
	~Controller();

private:

};

}
}
