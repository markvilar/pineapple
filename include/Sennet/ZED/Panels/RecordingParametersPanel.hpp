#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/RecordingParameters.hpp"

namespace Sennet { namespace ZED {

class RecordingParametersPanel
{
public:
	RecordingParametersPanel() = default;
	RecordingParametersPanel(const Ref<RecordingParameters>& context);

	void SetContext(const Ref<RecordingParameters>& context);
	void OnImGuiRender();

private:
	Ref<RecordingParameters> m_Context;
};

}}
