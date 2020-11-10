#include "Sennet/ZED/Panels/RecordClientPanel.hpp"

static void Strtrim(char* s)
{ 
	char* str_end = s + strlen(s); 
	while (str_end > s && str_end[-1] == ' ') 
		str_end--; 
	*str_end = 0; 
}

namespace Sennet { namespace ZED {

RecordClientPanel::RecordClientPanel(const Ref<RecordClient>& context)
{
	SetContext(context);
}

void RecordClientPanel::SetContext(const Ref<RecordClient>& context)
{
	m_Context = context;
}

void RecordClientPanel::OnImGuiRender()
{
	static char InputBuf[256];
	if (ImGui::InputText("Address", InputBuf, IM_ARRAYSIZE(InputBuf)))
	{
	}

	static ImU16 port = 0;
	ImGui::InputScalar("Port", ImGuiDataType_U16, &port, NULL, NULL, "%u");
	
	if (ImGui::SmallButton("Connect"))
	{
		if (m_Context && !m_Context->IsConnected())
		{
			m_Context->Connect(std::string(InputBuf), port);
		}
	}
	ImGui::SameLine();
	if (ImGui::SmallButton("Disconnect"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->Disconnect();
		}
	}

	ImGui::SameLine();
	ImGui::Text("Status: %s", m_Context && m_Context->IsConnected() ?
		"Connected" : "Not Connected");

	ImGui::Dummy(ImVec2(0.0f, 15.0f));
	ImGui::Columns(2, "Action Columns", true);

	if (ImGui::SmallButton("Ping Server"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->PingServer();
		}
	}
	if (ImGui::SmallButton("Synchronize Server"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->SynchronizeServer();
		}
	}

	if (ImGui::SmallButton("Initialize Recorder"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->InitializeRecorder();
		}
	}
	if (ImGui::SmallButton("Shutdown Recorder"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->ShutdownRecorder();
		}
	}
	
	ImGui::NextColumn();
	if (ImGui::SmallButton("Start Record"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->StartRecord();
		}
	}
	if (ImGui::SmallButton("Stop Record"))
	{
		if (m_Context && m_Context->IsConnected())
		{
			m_Context->StopRecord();
		}
	}
	
	ImGui::Columns(1);
}

}}
