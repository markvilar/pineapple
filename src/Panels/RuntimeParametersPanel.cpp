#include "Sennet/ZED/Panels/RuntimeParametersPanel.hpp"

namespace Sennet { namespace ZED {

RuntimeParametersPanel::RuntimeParametersPanel(const Ref<Client>& client)
{
	m_Client= client;
}

void RuntimeParametersPanel::SetClient(const Ref<Client>& client)
{
	m_Client= client;
}

void RuntimeParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Runtime Parameters"))
	{
		static const char* sensingModeOptions[] = { "None", 
			"Standard", "Fill" };
		ImGui::SliderInt("Sensing Mode", (int*)&m_Parameters.sensingMode,
			0, 2, sensingModeOptions[(int)m_Parameters.sensingMode]);

		static const char* referenceFrameOptions[] = { "None", 
			"World", "Camera" };
		ImGui::SliderInt("Reference Frame", 
			(int*)&m_Parameters.referenceFrame, 0, 2,
			referenceFrameOptions[(int)m_Parameters.referenceFrame]);

		ImGui::Checkbox("Enable Depth", &m_Parameters.enableDepth);

		static const ImU32 confThreshMin = 0;
		static const ImU32 confThreshMax = 100;
            	ImGui::SliderScalar("Confidence Theshold", 
			ImGuiDataType_U32,
			&m_Parameters.confidenceThreshold, 
			&confThreshMin, 
			&confThreshMax, 
			"%u");
			
		static const ImU32 textConfThreshMin = 0;
		static const ImU32 textConfThreshMax = 100;
            	ImGui::SliderScalar("Texture Confidence Theshold", 
			ImGuiDataType_U32,
			&m_Parameters.textureConfidenceThreshold,
			&textConfThreshMin, 
			&textConfThreshMax, 
			"%u");

		if (ImGui::SmallButton("Debug Runtime Parameters"))
		{
			SN_CORE_INFO("{0}", m_Parameters.ToString());
		}
	}
}

}}
