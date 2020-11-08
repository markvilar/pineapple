#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/ControlLayer.hpp"

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

int Sennet::main(int argc, char** argv)
{
	Sennet::Log::Init();
	auto app = Sennet::CreateApplication();
	app->Run();
	return 0;
}

int main(int argc, char** argv)
{	
	return Sennet::main(argc, argv);
}
