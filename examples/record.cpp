#include <filesystem>
#include <iostream>
#include <signal.h>

#include "Sennet/Sennet.hpp"

#include "Pineapple/Messages.hpp"
#include "Pineapple/SensorController.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int) { stopFlag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &interrupt_handler);

    Sennet::Log::Init();

    Pineapple::SensorController controller("/home/martin/Documents/");
    auto recordingParameters = controller.GetRecordingParameters();
    SENNET_INFO("Recording Parameters: {0}", recordingParameters.ToString());

    recordingParameters.filename = "testRecording.svo";
    controller.SetRecordingParameters(recordingParameters);

    recordingParameters = controller.GetRecordingParameters();
    SENNET_INFO("Recording Parameters: {0}", recordingParameters.ToString());

    controller.Initialize();
    controller.Start();

    while (!stopFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
