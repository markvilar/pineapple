#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class RuntimeParametersPanel
{
public:
	RuntimeParametersPanel() = default;
	RuntimeParametersPanel(const Ref<Client>& client);

	void SetClient(const Ref<Client>& client);

	void OnImGuiRender();

private:
	Ref<Client> m_Client;
	RuntimeParameters m_Parameters;
};

}}
