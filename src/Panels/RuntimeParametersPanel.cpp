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
		if (!m_Context)
		{
			ImGui::Text("No Context.");
			return;
		}

		static const char* sensingModeOptions[] = { "None", 
			"Standard", "Fill" };
		ImGui::SliderInt("Sensing Mode", (int*)&m_Context->sensingMode,
			0, 2, sensingModeOptions[(int)m_Context->sensingMode]);

		static const char* referenceFrameOptions[] = { "None", 
			"World", "Camera" };
		ImGui::SliderInt("Reference Frame", 
			(int*)&m_Context->referenceFrame, 0, 2,
			referenceFrameOptions[(int)m_Context->referenceFrame]);

		ImGui::Checkbox("Enable Depth", &m_Context->enableDepth);

		static const ImU32 confThreshMin = 0;
		static const ImU32 confThreshMax = 100;
            	ImGui::SliderScalar("Confidence Theshold", 
			ImGuiDataType_U32,
			&m_Context->confidenceThreshold, 
			&confThreshMin, 
			&confThreshMax, 
			"%u");
			
		static const ImU32 textConfThreshMin = 0;
		static const ImU32 textConfThreshMax = 100;
            	ImGui::SliderScalar("Texture Confidence Theshold", 
			ImGuiDataType_U32,
			&m_Context->textureConfidenceThreshold,
			&textConfThreshMin, 
			&textConfThreshMax, 
			"%u");

		if (ImGui::SmallButton("Debug Runtime Parameters"))
		{
			SN_CORE_INFO("{0}", m_Context->ToString());
		}
	}
}

}}
