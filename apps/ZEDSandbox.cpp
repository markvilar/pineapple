#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Recorder.hpp"
#include "Sennet/ZED/Parameters/Conversion.hpp"

void SleepThisThread(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void testRecorder()
{
	auto handle = Sennet::CreateScope<Sennet::ZED::Recorder>();
	handle->Initialize();
	handle->StartRecord();
	SleepThisThread(1000);

	auto [initParameters, recordingParameters, runtimeParameters] = 
		handle->GetParameters();
	SN_INFO(initParameters.ToString());

	int count = 0;
	int n = 10;

	while (count < n)
	{
		auto image = handle->GetImage(Sennet::ZED::View::SideBySide);
		if (image)
		{
			std::cout << *image << "\n";
			std::cout << 
				static_cast<int>(image->GetPixel(640, 360, 0))
				<< ", " << 
				static_cast<int>(image->GetPixel(640, 360, 1))
				<< ", " << 
				static_cast<int>(image->GetPixel(640, 360, 2))
				<< ", " << 
				static_cast<int>(image->GetPixel(640, 360, 3))
				<< "\n";
			count++;
			SleepThisThread(1000);
		}
	}
}

int main(int argc, char* argv[])
{
	Sennet::Log::Init();
	testRecorder();
	return 0;
}
