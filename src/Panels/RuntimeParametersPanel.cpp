#include "Sennet/ZED/Panels/RuntimeParametersPanel.hpp"

namespace Sennet { namespace ZED {

RuntimeParametersPanel::RuntimeParametersPanel(
	const Ref<RuntimeParameters>& context)
{
	SetContext(context);
}

void RuntimeParametersPanel::SetContext(
	const Ref<RuntimeParameters>& context)
{
	m_Context = context;
}

void RuntimeParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Runtime Parameters"))
	{
		if (ImGui::SmallButton("Debug Runtime Parameters"))
		{
			if (m_Context)
			{
				SN_CORE_INFO("{0}", m_Context->ToString());
			}
			else
			{
				SN_CORE_INFO("No context");
			}
		}
	}
}

}}
