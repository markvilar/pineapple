#include <SennetZED/Controller.hpp>

#include <GLFW/glfw3.h>

#include <SennetZED/Layers/ControlLayer.hpp>
#include <SennetZED/Layers/NetworkLayer.hpp>

namespace Sennet
{

namespace ZED
{

Controller::Controller(unsigned short port, uint64_t waitFor)
{
	PushLayer(new NetworkLayer(port, waitFor));
	PushLayer(new ControlLayer());
}

Controller::~Controller()
{
}

}
}
