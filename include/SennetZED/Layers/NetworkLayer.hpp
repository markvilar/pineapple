#pragma once
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

	void OnAttach() override;
	void OnDetach() override;
	
private:
	Sennet::ConnectionManager m_ConnectionManager;
};

}
}
