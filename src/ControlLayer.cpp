#include "Sennet/ZED/ControlLayer.hpp"

namespace Sennet { namespace ZED {

ControlLayer::ControlLayer()
	: Layer("ControlLayer"), m_CameraController(1280.0f / 720.0f, false)
{
}

ControlLayer::~ControlLayer()
{
}

void ControlLayer::OnAttach()
{
	// Set up client and parameters.
	m_Client = CreateRef<RecordClient>();
	m_InitParameters = CreateRef<InitParameters>();
	m_RecordingParameters = CreateRef<RecordingParameters>();
	m_RuntimeParameters = CreateRef<RuntimeParameters>();

	// Set up client panel.
	m_ClientPanel.SetContext(m_Client);
	m_ClientPanel.SetParameters(m_InitParameters);
	m_ClientPanel.SetParameters(m_RecordingParameters);
	m_ClientPanel.SetParameters(m_RuntimeParameters);

	// Set up parameter panels.
	m_InitParametersPanel.SetContext(m_InitParameters);
	m_RecordingParametersPanel.SetContext(m_RecordingParameters);
	m_RuntimeParametersPanel.SetContext(m_RuntimeParameters);

	// Set up texture and image.
	m_ImageTexture = Texture2D::Create(1, 1);
	m_Image = CreateRef<Image<uint8_t>>();
}

void ControlLayer::OnDetach()
{
}

void ControlLayer::OnUpdate(Timestep ts)
{
	while (!m_Client->Incoming().empty())
	{
		auto message = m_Client->Incoming().pop_front().Msg;
		OnMessage(message);
	}

	m_CameraController.OnUpdate(ts);

	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	RenderCommand::Clear();

	Renderer2D::BeginScene(m_CameraController.GetCamera());

	if (m_Image->GetSize() > 0 
		&& m_Image->GetWidth() != m_ImageTexture->GetWidth()
		&& m_Image->GetHeight() != m_ImageTexture->GetHeight())
	{
		m_ImageTexture = Texture2D::Create(m_Image->GetWidth(),
			m_Image->GetHeight(), 
			Texture::InternalFormat::RGBA8,
			Texture::DataFormat::BGRA);
	}
	else if (m_Image->GetSize() > 0 && m_Image->GetHeight() > 0 
		&& m_Image->GetWidth() == m_ImageTexture->GetWidth() 
		&& m_Image->GetHeight() == m_ImageTexture->GetHeight())
	{
		m_ImageTexture->SetData(m_Image->GetPtr(), m_Image->GetSize());
		float aspectRatio = (float)m_Image->GetWidth() 
			/ (float)m_Image->GetHeight();
		Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f },
			{ aspectRatio, -1.0f }, m_ImageTexture);
	}

	Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.6f, 0.9f }, 
		{ 0.8f, 0.2f, 0.3f, 1.0f });
	Renderer2D::EndScene();
}

void ControlLayer::OnImGuiRender()
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::SetNextWindowSize(ImVec2(520,600));
	if (ImGui::Begin("ZED"))
	{
		m_ClientPanel.OnImGuiRender();
		ImGui::Separator();
		m_InitParametersPanel.OnImGuiRender();
		m_RecordingParametersPanel.OnImGuiRender();
		m_RuntimeParametersPanel.OnImGuiRender();
		ImGui::End();
	}
}

void ControlLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
}

void ControlLayer::OnMessage(Message<MessageTypes>& message)
{
	switch (message.Header.ID)
	{
		case MessageTypes::ServerPing:
			m_ClientPanel.OnServerPing(message);
			break;
		case MessageTypes::RecorderActionAccept:
			SN_CORE_INFO("Recorder Action Accepted!");
			break;
		case MessageTypes::RecorderActionDeny:
			SN_CORE_INFO("Recorder Action Denied!");
			break;
		case MessageTypes::Image:
			uint32_t width, height, channels;
			message >> channels >> height >> width;
			m_Image = CreateRef<Image<uint8_t>>(width, height, 
				channels);
			message >> m_Image->GetBuffer();
			SN_CORE_INFO("Image: {0} ({1},{2},{3})",
				m_Image->GetSize(), m_Image->GetWidth(),
				m_Image->GetHeight(), m_Image->GetChannels());
			break;
	}
}

}}
