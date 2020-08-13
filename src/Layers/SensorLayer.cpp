#include <SennetZED/Layers/SensorLayer.hpp>

namespace Sennet
{

namespace ZED
{

SensorLayer::SensorLayer()
	: Layer("Sensor")
{
}

SensorLayer::~SensorLayer()
{
}

void SensorLayer::OnAttach()
{
}

void SensorLayer::OnDetach()
{
}

void SensorLayer::OnUpdate(Timestep ts)
{
}

void SensorLayer::OnMessage(Ref<Message> msg)
{
	SN_TRACE("[SensorLayer] Got message!");
}

}
}
