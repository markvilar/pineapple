#include "Sennet/ZED/Panels/RecordingParametersPanel.hpp"

namespace Sennet { namespace ZED {

RecordingParametersPanel::RecordingParametersPanel(
	const Ref<Client>& client)
{
	m_Client = client;
}

void RecordingParametersPanel::SetClient(const Ref<Client>& client)
{
	m_Client = client;
}

void RecordingParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Recording Parameters"))
	{
		static char InputBuf[256];
		if (ImGui::InputText("SVO Filename", InputBuf, 
			IM_ARRAYSIZE(InputBuf)))
		{
		}

		// TODO: SVO Compression Mode
		
		static ImU32 bitRate = 0;
		if (ImGui::InputScalar("Target Bitrate", ImGuiDataType_U32,
			&bitRate, NULL, NULL, "%u"))
		{
			m_Parameters.targetBitRate = bitRate;
		}

		static ImU32 frameRate = 0;
		if (ImGui::InputScalar("Target Framerate", ImGuiDataType_U32,
			&frameRate, NULL, NULL, "%u"))
		{
			m_Parameters.targetFrameRate = frameRate;
		}

		if (ImGui::SmallButton("Debug Recording Parameters"))
		{
			SN_CORE_INFO("{0}", m_Parameters.ToString());
		}
	}
}

}}
