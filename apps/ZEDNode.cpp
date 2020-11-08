#include <chrono>
#include <signal.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/RecordServer.hpp"

sig_atomic_t stopFlag = 0;

void interrupt_handler(int)
{
	stopFlag = 1;
}

int main(int argc, char** argv)
{	
	signal(SIGINT, &interrupt_handler);
	uint32_t nodeRate = 60;
	
	Sennet::Log::Init();

	Sennet::ZED::RecordServer server(60000, "/home/martin/Documents/");
	server.Start(); // TODO: Makes program not terminate.

	while (!stopFlag)
	{
		server.Update();
		std::this_thread::sleep_for(std::chrono::seconds(1 / nodeRate));
	}

	server.Stop();

	return 0;
}
