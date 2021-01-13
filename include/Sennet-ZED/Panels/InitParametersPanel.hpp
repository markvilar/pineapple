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

	void SetClient(const Ref<Client>& client);

	void SetServerParameters(const Ref<InitParameters>& parameters);

	void OnImGuiRender();

private:
	InitParameters m_Parameters;
	Ref<InitParameters> m_ServerParameters;

	Ref<Client> m_Client;
};

}}
