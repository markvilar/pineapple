#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

class RuntimeParametersPanel
{
public:
	RuntimeParametersPanel() = default;
	RuntimeParametersPanel(const Ref<RuntimeParameters>& context);

	void SetContext(const Ref<RuntimeParameters>& context);
	void OnImGuiRender();

private:
	Ref<RuntimeParameters> m_Context;
};

}}
