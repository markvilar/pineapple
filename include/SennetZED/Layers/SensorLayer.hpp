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

	virtual void OnUpdate(Timestep ts) override;

	virtual void OnMessage(Ref<Message> msg) override;

private:
	Recorder m_Recorder;
};

}
}
