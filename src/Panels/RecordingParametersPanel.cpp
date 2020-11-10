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
		if (!m_Context)
		{
			ImGui::Text("No Context Bound.");
			return;
		}

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
			m_Context->targetBitRate = bitRate;
		}

		static ImU32 frameRate = 0;
		if (ImGui::InputScalar("Target Framerate", ImGuiDataType_U32,
			&frameRate, NULL, NULL, "%u"))
		{
			m_Context->targetFrameRate = frameRate;
		}

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
