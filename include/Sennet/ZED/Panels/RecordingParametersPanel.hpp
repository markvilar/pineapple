#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"

namespace Sennet { namespace ZED {

class RecordingParametersPanel
{
public:
	RecordingParametersPanel() = default;
	RecordingParametersPanel(const Ref<Client>& client);

	void SetClient(const Ref<Client>& client);

	void OnImGuiRender();

private:
	Ref<Client> m_Client;
	RecordingParameters m_Parameters;
};

}}
