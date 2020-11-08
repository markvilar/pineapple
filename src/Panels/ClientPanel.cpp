#include "Sennet/ZED/Panels/ClientPanel.hpp"

static void Strtrim(char* s)
{ 
	char* str_end = s + strlen(s); 
	while (str_end > s && str_end[-1] == ' ') 
		str_end--; 
	*str_end = 0; 
}

namespace Sennet { namespace ZED {

ClientPanel::ClientPanel(const Ref<Client<MessageTypes>>& context)
{
	SetContext(context);
}

void ClientPanel::SetContext(const Ref<Client<MessageTypes>>& context)
{
	m_Context = context;
}

void ClientPanel::OnImGuiRender()
{
	static char InputBuf[256];
	static bool reclaim_focus = false;
	ImGuiInputTextFlags input_text_flags = 
		ImGuiInputTextFlags_EnterReturnsTrue 
		| ImGuiInputTextFlags_CallbackCompletion 
		| ImGuiInputTextFlags_CallbackHistory;
	if (ImGui::InputText("Address", InputBuf, 
		IM_ARRAYSIZE(InputBuf), input_text_flags))
	{
		char* s = InputBuf;
		Strtrim(s);
		if (s[0])
		{
			//ExecCommand(s);
		}
		strcpy(s, "");
		reclaim_focus = true;
	}

	static ImU16 port = 0;
	ImGui::SameLine();
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
}

}}
