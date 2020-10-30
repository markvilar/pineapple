#include <iostream>

#include <sl/Camera.hpp>

#include "Sennet/Sennet.hpp"

int main()
{
	Sennet::Log::Init();
	SN_INFO("Hello world!");

	sl::Camera camera;

	auto error = camera.open();
	if (error != sl::ERROR_CODE::SUCCESS)
	{
		std::cout << sl::toString(error) << std::endl;
	}
	else
	{
		std::cout << "Opened camera!" << std::endl;
		camera.close();
	}
	
	return 0;
}
