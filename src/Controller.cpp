#include <SennetZED/Controller.hpp>

#include <GLFW/glfw3.h>

#include <SennetZED/Layers/ControlLayer.hpp>
#include <SennetZED/Layers/NetworkLayer.hpp>
#include <SennetZED/Layers/StateLayer.hpp>

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
