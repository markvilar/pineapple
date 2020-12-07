#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"
#include "Sennet/ZED/Messages.hpp"

enum class DefaultMessageTypes: uint32_t
{
	ServerPing			= 0,
	ServerSynchronize		= 1,
	ServerAccept			= 2,
	ServerDeny			= 3,
};

namespace Sennet {

class DefaultClientPanel
{
public:
	DefaultClientPanel() = default;
	DefaultClientPanel(const Ref<Client<DefaultMessageTypes>>& context);

	void SetClient(const Ref<Client<DefaultMessageTypes>>& client);

	void OnImGuiRender();

	void OnServerPing(Message<DefaultMessageTypes>& message);
	void OnServerSynchronize(Message<DefaultMessageTypes>& message);
	void OnServerAccept(Message<DefaultMessageTypes>& message);
	void OnServerDeny(Message<DefaultMessageTypes>& message);

private:
	Ref<Client<DefaultMessageTypes>> m_Client;
};

}
