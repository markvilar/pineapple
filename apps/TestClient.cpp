#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"

class TestClient : public Sennet::Client<Sennet::ZED::MessageTypes>
{
public:
	void PingServer()
	{
		Sennet::Message<Sennet::ZED::MessageTypes> message;
		message.Header.ID = Sennet::ZED::MessageTypes::ServerPing;
		std::chrono::system_clock::time_point time = 
			std::chrono::system_clock::now();

		message << time;
		SN_INFO("Message size: {0}", message.Size());
		SN_INFO("Message body size: {0}", message.Body.size());
		Send(message);
	}
};

int main()
{
	Sennet::Log::Init();
	
	TestClient client;
	client.Connect("127.0.0.1", 60000);

	bool quit = false;
	bool sent = false;
	while (!quit)
	{
		if (client.IsConnected())
		{
			if (!sent)
			{
				std::this_thread::sleep_for(
					std::chrono::seconds(1));
				SN_INFO("Pinging server!");
				client.PingServer();
				sent = true;
			}
			if (!client.Incoming().empty())
			{
				auto message = client.Incoming().pop_front().Msg;

				switch (message.Header.ID)
				{
				case Sennet::ZED::MessageTypes::ServerPing:
					std::chrono::system_clock::time_point t =
						std::chrono::system_clock::now();
					std::chrono::system_clock::time_point z;
					message >> z;
					auto time = std::chrono::duration<double>
						(t - z).count();
					SN_INFO("Ping: {0}", time);
					break;
				}
			}
		}
		else
		{
			SN_INFO("Server Down.");
			quit = true;
		}
	}

	return 0;
}
