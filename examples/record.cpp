#include <filesystem>
#include <iostream>
#include <signal.h>

#include "Pine/Pine.hpp"

#include "Pineapple/CameraInterface.hpp"
#include "Pineapple/Messages.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int) { stopFlag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &interrupt_handler);

    Pine::Log::Init();

    Pineapple::ZED::CameraInterface interface("/home/martin/Documents/");

    interface.StartRecord();

    while (!stopFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    interface.StopRecord();

    return 0;
}
