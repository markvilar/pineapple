#pragma once
#include <Sennet/Sennet.hpp>

#include <SennetZED/Recorder.hpp>
#include <SennetZED/Messages/Request.hpp>
#include <SennetZED/Messages/Response.hpp>

namespace Sennet
{

namespace ZED
{

class SensorLayer : public Sennet::Layer
{
public:
	SensorLayer();
	virtual ~SensorLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Sennet::Timestep ts) override;

	virtual void OnMessage(Sennet::Ref<Sennet::Message> msg) override;

private:
	bool OnCommandRequest(Ref<CommandRequest> msg);
	bool OnSettingsRequest(Ref<SettingsRequest> msg);
	bool OnStateRequest(Ref<StateRequest> msg);

	void SubmitStateResponse(const std::string address, 
		const unsigned short port);

private:
	Sennet::Scope<Recorder> m_Recorder;
};

}
}
