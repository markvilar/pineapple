#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"

namespace Sennet { namespace ZED {

class ClientPanel
{
public:
	ClientPanel() = default;
	ClientPanel(const Ref<Client<MessageTypes>>& context);

	void SetContext(const Ref<Client<MessageTypes>>& context);
	void OnImGuiRender();

private:
	Ref<Client<MessageTypes>> m_Context;
};

}}
