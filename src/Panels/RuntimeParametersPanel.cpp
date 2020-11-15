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
		const char* sensingLabels[] = { "None", "Standard", "Fill" };
		SensingMode sensingOptions[] = { SensingMode::None, 
			SensingMode::Standard, SensingMode::Fill };
		static_assert(sizeof(sensingLabels) / sizeof(sensingLabels[0])
			== sizeof(sensingOptions) / sizeof(sensingOptions[0]),
			"Sensing mode labels and options must be of equal "
			"size.");
		static int sensingIndex = 1;
		const char* sensingLabel = sensingLabels[sensingIndex];
		if (ImGui::BeginCombo("Sensing Mode", sensingLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(sensingLabels); n++)
			{
				const bool isSelected =
					(m_Parameters.sensingMode
					== sensingOptions[n]);
				if (ImGui::Selectable(sensingLabels[n], 
					isSelected))
				{
					sensingIndex = n;
					m_Parameters.sensingMode = 
						sensingOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		const char* refLabels[] = { "None", "World", "Camera" };
		ReferenceFrame refOptions[] = { ReferenceFrame::None, 
			ReferenceFrame::World, ReferenceFrame::Camera };
		static_assert(sizeof(refLabels) / sizeof(refLabels[0])
			== sizeof(refOptions) / sizeof(refOptions[0]),
			"Reference frame labels and options must be of equal "
			"size.");
		static int refIndex = 2;
		const char* refLabel = refLabels[refIndex];
		if (ImGui::BeginCombo("Reference Frame", refLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(refLabels); n++)
			{
				const bool isSelected =
					(m_Parameters.referenceFrame
					== refOptions[n]);
				if (ImGui::Selectable(refLabels[n], isSelected))
				{
					refIndex = n;
					m_Parameters.referenceFrame = 
						refOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Checkbox("Enable Depth", &m_Parameters.enableDepth);

		static const ImU32 confThreshMin = 0;
		static const ImU32 confThreshMax = 100;
            	ImGui::SliderScalar("Conf. Theshold", 
			ImGuiDataType_U32,
			&m_Parameters.confidenceThreshold, 
			&confThreshMin, 
			&confThreshMax, 
			"%u");
			
		static const ImU32 textConfThreshMin = 0;
		static const ImU32 textConfThreshMax = 100;
            	ImGui::SliderScalar("Text. Conf. Theshold", 
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
