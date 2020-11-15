#include "Sennet/ZED/Panels/ClientPanel.hpp"

static void Strtrim(char* s)
{ 
	char* str_end = s + strlen(s); 
	while (str_end > s && str_end[-1] == ' ') 
		str_end--; 
	*str_end = 0; 
}

namespace Sennet { namespace ZED {

ClientPanel::ClientPanel(const Ref<Client>& client)
{
	m_Client = client;
}

void ClientPanel::SetClient(const Ref<Client>& client)
{
	m_Client = client;
}

void ClientPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Client"))
	{
		static char InputBuf[256];
		if (ImGui::InputText("Address", InputBuf, 
			IM_ARRAYSIZE(InputBuf)))
		{
		}

		static ImU16 port = 0;
		ImGui::InputScalar("Port", ImGuiDataType_U16, &port, NULL, 
			NULL, "%u");
		
		if (ImGui::SmallButton("Connect"))
		{
			if (m_Client && !m_Client->IsConnected())
			{
				m_Client->Connect(std::string(InputBuf), port);
			}
		}
		ImGui::SameLine();
		if (ImGui::SmallButton("Disconnect"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				m_Client->Disconnect();
			}
		}

		ImGui::SameLine();
		ImGui::Text("Status: %s", m_Client && m_Client->IsConnected() ?
			"Connected" : "Not Connected");

		ImGui::Dummy(ImVec2(0.0f, 15.0f));
		ImGui::Columns(2, "Action Columns", true);

		if (ImGui::SmallButton("Ping Server"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				m_Client->RequestServerPing();
			}
		}
		if (ImGui::SmallButton("Synchronize Server"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				m_Client->RequestServerSynchronization();
			}
		}

		ImGui::NextColumn();
		
		ImGui::Columns(1);
	}
}

void ClientPanel::OnServerPing(Message<MessageTypes>& message)
{
	std::chrono::system_clock::time_point timeNow = 
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point timeThen;
	message >> timeThen;
	auto duration = std::chrono::duration<double>(timeNow-timeThen).count();
	SN_CORE_INFO("Server Ping: {0}", duration);
}

void ClientPanel::OnServerSynchronize(Message<MessageTypes>& message)
{
	SN_CORE_INFO("Server Synchronize.");
}

void ClientPanel::OnServerAccept(Message<MessageTypes>& message)
{
	SN_CORE_INFO("Server Accept.");
}

void ClientPanel::OnServerDeny(Message<MessageTypes>& message)
{
	SN_CORE_INFO("Server Deny.");
}

}}
