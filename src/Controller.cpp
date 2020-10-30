#include "Sennet/ZED/Controller.hpp"

#include "GLFW/glfw3.h"

#include "Sennet/ZED/Layers/ControlLayer.hpp"
#include "Sennet/ZED/Layers/NetworkLayer.hpp"
#include "Sennet/ZED/Layers/StateLayer.hpp"

namespace Sennet
{

namespace ZED
{

Controller::Controller(unsigned short port, uint64_t waitFor, bool verbose)
	: Sennet::Application(verbose)
{
	PushLayer(new NetworkLayer(port, waitFor));
	PushLayer(new StateLayer());
	PushLayer(new ControlLayer());
}

Controller::~Controller()
{
}

}
}
