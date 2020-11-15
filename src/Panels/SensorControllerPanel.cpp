#include "Sennet/ZED/Panels/SensorControllerPanel.hpp"

namespace Sennet { namespace ZED {

void SensorControllerPanel::SetClient(const Ref<Client>& client)
{
	m_Client = client;
}

void SensorControllerPanel::OnImGuiRender()
{
	if (ImGui::SmallButton("Initialize"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestSensorControllerInitialization();
		}
	}
	if (ImGui::SmallButton("Shutdown"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestSensorControllerShutdown();
		}
	}
	
	if (ImGui::SmallButton("Start"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestSensorControllerStart();
		}
	}
	if (ImGui::SmallButton("Stop"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestSensorControllerStop();
		}
	}
	if (ImGui::SmallButton("Request Settings"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestSettings();
		}
	}
	if (ImGui::SmallButton("Request Image"))
	{
		if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestImage();
		}
	}
}

void SensorControllerPanel::OnSensorControllerAccept(
	Message<MessageTypes>& message)
{
	SN_CORE_INFO("Sensor Controller Accepted!");
}

void SensorControllerPanel::OnSensorControllerDeny(
	Message<MessageTypes>& message)
{
	SN_CORE_INFO("Sensor Controller Denied!");
}

void SensorControllerPanel::OnImage(const Ref<Image<uint8_t>>& image)
{
	m_Image = image;
}

}}
