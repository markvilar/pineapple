#include "Sennet/ZED/Panels/InitParametersPanel.hpp"

namespace Sennet { namespace ZED {

InitParametersPanel::InitParametersPanel(const Ref<InitParameters>& context)
{
	SetContext(context);
}

void InitParametersPanel::SetContext(const Ref<InitParameters>& context)
{
	m_Context = context;
}

void InitParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Initialization Parameters"))
	{
		if (ImGui::SmallButton("Debug Initialization Parameters"))
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
