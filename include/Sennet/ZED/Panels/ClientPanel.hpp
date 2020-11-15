#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"
#include "Sennet/ZED/Messages.hpp"

namespace Sennet { namespace ZED {

class ClientPanel
{
public:
	ClientPanel() = default;
	ClientPanel(const Ref<Client>& context);

	void SetClient(const Ref<Client>& client);

	void OnImGuiRender();

	void OnServerPing(Message<MessageTypes>& message);
	void OnServerSynchronize(Message<MessageTypes>& message);
	void OnServerAccept(Message<MessageTypes>& message);
	void OnServerDeny(Message<MessageTypes>& message);

private:
	Ref<Client> m_Client;
};

}}
