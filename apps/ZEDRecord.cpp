#include <filesystem>
#include <iostream>
#include <signal.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/SensorController.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int)
{
	stopFlag = 1;
}

int main()
{
	// Set up interrupt handler.
	signal(SIGINT, &interrupt_handler);

	Sennet::Log::Init();

	// Initialize controller and get recording parameters.
	Sennet::ZED::SensorController controller("/home/martin/Documents/");
	auto recordingParameters = controller.GetRecordingParameters();
	SN_INFO("Recording Parameters: {0}", recordingParameters.ToString());

	// Update recording parameters.
	recordingParameters.filename = "testRecording.svo";
	controller.SetRecordingParameters(recordingParameters);

	// Get new recording parameters.
	recordingParameters = controller.GetRecordingParameters();
	SN_INFO("Recording Parameters: {0}", recordingParameters.ToString());

	controller.Initialize();
	controller.Start();

	while (!stopFlag)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
