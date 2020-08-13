#include <SennetZED/Layers/NetworkLayer.hpp>

namespace Sennet
{

namespace ZED
{

NetworkLayer::NetworkLayer(const unsigned short port, uint64_t waitFor)
	: Layer("Network"), m_ConnectionManager(port, waitFor)
{
	if (Sennet::Application::GetPtr())
	{
		m_ConnectionManager.SetMessageCallback(std::bind(
			&Sennet::Application::OnMessage, 
			&Sennet::Application::Get(),
			std::placeholders::_1));

	}
	else if (Sennet::Node::GetPtr())
	{
		m_ConnectionManager.SetMessageCallback(std::bind(
			&Sennet::Node::OnMessage, 
			&Sennet::Node::Get(), 
			std::placeholders::_1));
	}
}

void NetworkLayer::OnAttach()
{
	m_ConnectionManager.Start();
}

void NetworkLayer::OnDetach()
{
}

}
}
