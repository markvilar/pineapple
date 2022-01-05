#include "Pineapple/Panels/RecordingParametersPanel.hpp"

namespace Pineapple
{

RecordingParametersPanel::RecordingParametersPanel(
    const Pine::Ref<Client>& client)
{
    m_Client = client;
}

void RecordingParametersPanel::SetClient(const Pine::Ref<Client>& client)
{
    m_Client = client;
}

void RecordingParametersPanel::OnImGuiRender()
{
    if (ImGui::Begin("Recording Parameters"))
    {
        const char* svoLabels[] = {"None", "Lossless", "H264", "H265"};
        SVOCompressionMode svoOptions[] = {SVOCompressionMode::None,
            SVOCompressionMode::Lossless,
            SVOCompressionMode::H264,
            SVOCompressionMode::H265};
        static_assert(sizeof(svoLabels) / sizeof(svoLabels[0])
                == sizeof(svoOptions) / sizeof(svoOptions[0]),
            "SVO compression mode labels and options must be of "
            "equal size.");
        static int svoIndex = 2;
        const char* svoLabel = svoLabels[svoIndex];
        if (ImGui::BeginCombo("SVO Compression Mode", svoLabel))
        {
            for (int n = 0; n < IM_ARRAYSIZE(svoLabels); n++)
            {
                const bool isSelected =
                    (m_Parameters.compressionMode == svoOptions[n]);
                if (ImGui::Selectable(svoLabels[n], isSelected))
                {
                    svoIndex = n;
                    m_Parameters.compressionMode = svoOptions[n];
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        static ImU32 bitRate = 0;
        if (ImGui::InputScalar("Target Bitrate",
                ImGuiDataType_U32,
                &bitRate,
                NULL,
                NULL,
                "%u"))
        {
            m_Parameters.targetBitRate = bitRate;
        }

        static ImU32 frameRate = 0;
        if (ImGui::InputScalar("Target Framerate",
                ImGuiDataType_U32,
                &frameRate,
                NULL,
                NULL,
                "%u"))
        {
            m_Parameters.targetFrameRate = frameRate;
        }

        if (ImGui::SmallButton("Update Recording Parameters"))
        {
            if (m_Client && m_Client->IsConnected())
            {
                m_Client->RequestRecordingParametersUpdate(m_Parameters);
            }
        }

        if (ImGui::SmallButton("Debug Recording Parameters"))
        {
            PINE_INFO("{0}", m_Parameters.ToString());
        }
    }
}

} // namespace Pineapple
