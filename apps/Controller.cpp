#include "Sennet/Sennet.hpp"

#include "Sennet-ZED/ControlLayer.hpp"

class Controller : public Sennet::Application
{
public:
	Controller() : Application()
	{
		PushLayer(new Sennet::ZED::ControlLayer());
	}

	~Controller()
	{
	}
};

Sennet::Application* Sennet::CreateApplication()
{
	return new Controller();
}

int main(int argc, char** argv)
{	
	Sennet::Log::Init();
	auto app = Sennet::CreateApplication();
	app->Run();
	return 0;
}
