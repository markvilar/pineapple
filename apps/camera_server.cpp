#include <chrono>
#include <signal.h>

#include <Pine/Pine.hpp>

#include "Pineapple/Messages.hpp"
#include "Pineapple/Server.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int) { stopFlag = 1; }

int main(int argc, char** argv)
{
    signal(SIGINT, &interrupt_handler);
    uint32_t nodeRate = 60;

    Pine::Log::Init();

    /*
    Pineapple::Server server(60000, "/home/martin/data/");
    server.Start(); // Note: Makes program not terminate.

    while (!stopFlag)
    {
        server.Update();
        std::this_thread::sleep_for(std::chrono::seconds(1 / nodeRate));
    }
    */

    return 0;
}
