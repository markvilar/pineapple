#include <Sennet/Sennet.hpp>

#include <SennetZED/Controller.hpp>
#include <SennetZED/Messages/ZEDMessage.hpp>

// Register messages.
namespace
{

zpp::serializer::register_types<
	zpp::serializer::make_type<Sennet::TextMessage,
	zpp::serializer::make_id("Sennet::TextMessage")>,
	zpp::serializer::make_type<Sennet::ImageMessage,
	zpp::serializer::make_id("Sennet::ImageMessage")>,
	zpp::serializer::make_type<Sennet::ZED::CommandRequest,
	zpp::serializer::make_id("Sennet::ZED::CommandRequest")>,
	zpp::serializer::make_type<Sennet::ZED::SettingsRequest,
	zpp::serializer::make_id("Sennet::ZED::SettingsRequest")>,
	zpp::serializer::make_type<Sennet::ZED::StateRequest,
	zpp::serializer::make_id("Sennet::ZED::StateRequest")>,
	zpp::serializer::make_type<Sennet::ZED::CommandResponse,
	zpp::serializer::make_id("Sennet::ZED::CommandResponse")>,
	zpp::serializer::make_type<Sennet::ZED::SettingsResponse,
	zpp::serializer::make_id("Sennet::ZED::SettingsResponse")>,
	zpp::serializer::make_type<Sennet::ZED::StateResponse,
	zpp::serializer::make_id("Sennet::ZED::StateResponse")>
> _;

}

Sennet::Application* Sennet::CreateApplication()
{
	unsigned short port = 6000;
	uint64_t waitFor = 1;
	return new Sennet::ZED::Controller(port, waitFor);
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
