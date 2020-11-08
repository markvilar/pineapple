#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/InitParameters.hpp"

namespace Sennet { namespace ZED {

class InitParametersPanel
{
public:
	InitParametersPanel() = default;
	InitParametersPanel(const Ref<InitParameters>& context);

	void SetContext(const Ref<InitParameters>& context);
	void OnImGuiRender();

private:
	Ref<InitParameters> m_Context;
};

}}
