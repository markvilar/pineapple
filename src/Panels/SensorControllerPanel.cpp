#include "Sennet-ZED/Panels/SensorControllerPanel.hpp"

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
		if (m_Client && m_Client->IsConnected() && m_OptionImageStream)
		{
			m_Client->RequestImageStream();
		}
		else if (m_Client && m_Client->IsConnected())
		{
			m_Client->RequestImage();
		}
	}

	ImGui::SameLine();
	ImGui::Checkbox("Image Stream", &m_OptionImageStream);
}

void SensorControllerPanel::UpdateImageTexture()
{
	if (!m_ImageTexture and m_Image)
	{
		m_ImageTexture = Texture2D::Create(m_Image->GetWidth(),
			m_Image->GetHeight(), Texture::InternalFormat::RGBA8,
			Texture::DataFormat::BGRA);
		m_ImageTexture->SetData(m_Image->GetPtr(), m_Image->GetSize());
	}
	else if (m_ImageTexture->GetWidth() != m_Image->GetWidth() 
		|| m_ImageTexture->GetHeight() != m_Image->GetHeight())
	{
		m_ImageTexture = Texture2D::Create(m_Image->GetWidth(),
			m_Image->GetHeight(), Texture::InternalFormat::RGBA8,
			Texture::DataFormat::BGRA);
		m_ImageTexture->SetData(m_Image->GetPtr(), m_Image->GetSize());
	}
	else
	{
		m_ImageTexture->SetData(m_Image->GetPtr(), m_Image->GetSize());
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

void SensorControllerPanel::OnImage(Message<MessageTypes>& message)
{
	uint32_t width, height, channels;
	message >> channels >> height >> width;
	auto image = CreateRef<Image<uint8_t>>(width, height, 
		channels);
	message >> image->GetBuffer();
	m_Image = image;
}

void SensorControllerPanel::OnImageStream(Message<MessageTypes>& message)
{
	if (m_OptionImageStream && m_Client && m_Client->IsConnected())
	{
		m_Client->RequestImageStream();
	}
	uint32_t width, height, channels;
	message >> channels >> height >> width;
	auto image = CreateRef<Image<uint8_t>>(width, height, 
		channels);
	message >> image->GetBuffer();
	m_Image = image;
}

}}
