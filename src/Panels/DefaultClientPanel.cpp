#include "Sennet/ZED/Panels/DefaultClientPanel.hpp"

static void Strtrim(char* s)
{ 
	char* str_end = s + strlen(s); 
	while (str_end > s && str_end[-1] == ' ') 
		str_end--; 
	*str_end = 0; 
}

namespace Sennet {

DefaultClientPanel::DefaultClientPanel(const Ref<Client<DefaultMessageTypes>>& client)
{
	m_Client = client;
}

void DefaultClientPanel::SetClient(const Ref<Client<DefaultMessageTypes>>& client)
{
	m_Client = client;
}

void DefaultClientPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Default Client"))
	{
		auto windowWidth = ImGui::GetWindowWidth();

		static char defaultClientAddress[256];
		ImGui::PushItemWidth(windowWidth * 0.66f);
		if (ImGui::InputText("Address 2", defaultClientAddress, 
			IM_ARRAYSIZE(defaultClientAddress)))
		{
		}

		static ImU16 defaultClientPort = 0;
		ImGui::PushItemWidth(windowWidth * 0.66f);
		ImGui::InputScalar("Port 2", ImGuiDataType_U16, 
			&defaultClientPort, NULL, NULL, "%u");
		
		if (ImGui::Button("Connect 2", ImVec2(windowWidth * 0.33f, 0)))
		{
			if (m_Client && !m_Client->IsConnected())
			{
				m_Client->Connect(
					std::string(defaultClientAddress), 
					defaultClientPort);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Disconnect 2", 
			ImVec2(windowWidth * 0.33f, 0)))
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

		if (ImGui::Button("Ping Server 2"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				Message<DefaultMessageTypes> message;
				message.Header.ID = 
					DefaultMessageTypes::ServerPing;
				std::chrono::system_clock::time_point time =
					std::chrono::system_clock::now();
				
				message << time;
				m_Client->Send(message);
			}
		}

		if (ImGui::Button("Synchronize Server 2"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				Message<DefaultMessageTypes> message;
				message.Header.ID = 
					DefaultMessageTypes::ServerSynchronize;
				m_Client->Send(message);
			}
		}

		ImGui::NextColumn();
		
		ImGui::Columns(1);
	}
}

void DefaultClientPanel::OnServerPing(Message<DefaultMessageTypes>& message)
{
	std::chrono::system_clock::time_point timeNow = 
		std::chrono::system_clock::now();
	std::chrono::system_clock::time_point timeThen;
	message >> timeThen;
	auto duration = std::chrono::duration<double>(timeNow-timeThen).count();
	SN_CORE_INFO("Server Ping: {0}", duration);
}

void DefaultClientPanel::OnServerSynchronize(
	Message<DefaultMessageTypes>& message)
{
	SN_CORE_INFO("Server Synchronize.");
	Timestamp localTime;
	localTime.Grab();
	Timestamp remoteTime;
	uint64_t ms;
	message >> ms;
	remoteTime.SetMilliseconds(ms);
	Sennet::Synchronizer::Get().WriteEntry("Topside", localTime, 
		"UHI", remoteTime);
}

void DefaultClientPanel::OnServerAccept(Message<DefaultMessageTypes>& message)
{
	SN_CORE_INFO("Server Accept.");
}

void DefaultClientPanel::OnServerDeny(Message<DefaultMessageTypes>& message)
{
	SN_CORE_INFO("Server Deny.");
}

}
