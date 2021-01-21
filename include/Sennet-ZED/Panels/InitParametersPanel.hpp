#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet-ZED/InitParameters.hpp"
#include "Sennet-ZED/Client.hpp"

namespace Sennet { namespace ZED {

class InitParametersPanel
{
public:
	InitParametersPanel() = default;
	~InitParametersPanel() = default;

	void SetClient(const Ref<Client>& client) { m_Client = client; } 

	void OnImGuiRender();

private:
	Ref<Client> m_Client;
	InitParameters m_Parameters;
};

}}
