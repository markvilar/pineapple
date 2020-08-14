#pragma once

#include <imgui.h>

#include <Sennet/Sennet.hpp>

namespace Sennet
{

namespace ZED
{

class NetworkLayer : public Sennet::Layer
{
public:
	NetworkLayer(const unsigned short port, uint64_t waitFor);
	~NetworkLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(Event& event) override;
	virtual void OnMessage(Ref<Message> msg) override;

private:
	void Connect(const std::string address, const std::string port);

	void RenderNetworkWindow();
	void RenderNetworkWindowConnect();
	void RenderNetworkWindowConnections();

private:
	Sennet::ConnectionManager m_ConnectionManager;
};

}
}
