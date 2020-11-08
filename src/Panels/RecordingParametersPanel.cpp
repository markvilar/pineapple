#include "Sennet/ZED/Panels/RecordingParametersPanel.hpp"

namespace Sennet { namespace ZED {

RecordingParametersPanel::RecordingParametersPanel(
	const Ref<RecordingParameters>& context)
{
	SetContext(context);
}

void RecordingParametersPanel::SetContext(
	const Ref<RecordingParameters>& context)
{
	m_Context = context;
}

void RecordingParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Recording Parameters"))
	{
		if (ImGui::SmallButton("Debug Recording Parameters"))
		{
			if (m_Context)
			{
				SN_CORE_INFO("{0}", m_Context->ToString());
			}
			else
			{
				SN_CORE_INFO("No context.");
			}
		}
	}
}

}}
