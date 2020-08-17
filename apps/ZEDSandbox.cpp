#include <chrono>
#include <iostream>
#include <thread>

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

#include <SennetZED/Recorder.hpp>
#include <SennetZED/Primitives/Conversion.hpp>
#include <SennetZED/Primitives/IO.hpp>

void test_params()
{
	Sennet::ZED::InitParameters init_params;
	Sennet::ZED::RecordingParameters rec_params;
	Sennet::ZED::RuntimeParameters run_params;

	std::cout << init_params << "\n";
	std::cout << rec_params << "\n";
	std::cout << run_params << "\n";
}

void test_SennetToStereolabs()
{
	Sennet::ZED::InitParameters init_params;
	Sennet::ZED::RecordingParameters rec_params;
	Sennet::ZED::RuntimeParameters run_params;

	std::cout << init_params << "\n";
	std::cout << SennetToStereolabs(init_params) << "\n";

	std::cout << rec_params << "\n";
	std::cout << SennetToStereolabs(rec_params) << "\n";

	std::cout << run_params << "\n";
	std::cout << SennetToStereolabs(run_params) << "\n";
}

void test_StereolabsToSennet()
{
	sl::InitParameters init_params;
	sl::RecordingParameters rec_params;
	sl::RuntimeParameters run_params;

	std::cout << init_params << "\n";
	std::cout << StereolabsToSennet(init_params) << "\n";	

	std::cout << rec_params << "\n";
	std::cout << StereolabsToSennet(rec_params) << "\n";

	std::cout << run_params << "\n";
	std::cout << StereolabsToSennet(run_params) << "\n";

}

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
			std::cout << static_cast<int>(image->GetPixel(640, 360, 0))
				<< ", " 
				<< static_cast<int>(image->GetPixel(640, 360, 1))
				<< ", " 
				<< static_cast<int>(image->GetPixel(640, 360, 2))
				<< ", " 
				<< static_cast<int>(image->GetPixel(640, 360, 3))
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
