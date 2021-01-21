#include "Sennet-ZED/ControlLayer.hpp"

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
	// Set up client.
	m_Client = CreateRef<Client>();

	// Set up panels.
	m_ClientPanel.SetClient(m_Client);
	m_InitParametersPanel.SetClient(m_Client);
	m_RecordingParametersPanel.SetClient(m_Client);
	m_RuntimeParametersPanel.SetClient(m_Client);
	m_SensorControllerPanel.SetClient(m_Client);

	// Set up framebuffer.
	FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Framebuffer::Create(fbSpec);

	Renderer2D::Init();

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

	FramebufferSpecification spec = m_Framebuffer->GetSpecification();
	if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
		(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
	{
		m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, 
			(uint32_t)m_ViewportSize.y);
		m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
	}

	if (m_ViewportFocused)
		m_CameraController.OnUpdate(ts);

	m_Framebuffer->Bind();
	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	RenderCommand::Clear();

	Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	if (m_SensorControllerPanel.HasImage())
	{
		m_SensorControllerPanel.UpdateImageTexture();
		auto imageTexture = m_SensorControllerPanel.GetImageTexture();
		float aspectRatio = (float)imageTexture->GetWidth() 
			/ (float)imageTexture->GetHeight();
		Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 
			{ aspectRatio, -1.0f }, imageTexture);
	}
	else
	{
		Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 
			{ 1.76f, -1.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
	}

	Renderer2D::EndScene();
	m_Framebuffer->Unbind();
}

void ControlLayer::OnImGuiRender()
{
	static bool dockspaceOpen = true;
	static bool optionFullscreenPersistant = true;
	bool optionFullscreen = optionFullscreenPersistant;
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar 
		| ImGuiWindowFlags_NoDocking;
	if (optionFullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar 
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize 
			| ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus 
			| ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		windowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &dockspaceOpen, windowFlags);
	ImGui::PopStyleVar();
	
	if (optionFullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Draw panels.
	m_ClientPanel.OnImGuiRender();
	m_InitParametersPanel.OnImGuiRender();
	m_SensorControllerPanel.OnImGuiRender();
	m_RecordingParametersPanel.OnImGuiRender();
	m_RuntimeParametersPanel.OnImGuiRender();
	

	// Viewport window.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");

	m_ViewportFocused = ImGui::IsWindowFocused();
	m_ViewportHovered = ImGui::IsWindowHovered();
	Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused 
		|| !m_ViewportHovered);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, 
		viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void ControlLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
}

void ControlLayer::OnMessage(Message<MessageTypes>& message)
{
	switch (message.Header.ID)
	{
		// Server messages.
		case MessageTypes::ServerPing:
			m_ClientPanel.OnServerPing(message);
			break;
		case MessageTypes::ServerAccept:
			m_ClientPanel.OnServerAccept(message);
			break;
		case MessageTypes::ServerDeny:
			m_ClientPanel.OnServerDeny(message);
			break;

		// Sensor control messages.
		case MessageTypes::SensorControllerAccept:
			m_SensorControllerPanel.OnSensorControllerAccept(message);
			break;
		case MessageTypes::SensorControllerDeny:
			m_SensorControllerPanel.OnSensorControllerDeny(message);
			break;

		// Image and image stream messages.
		case MessageTypes::Image:
			m_SensorControllerPanel.OnImage(message);
			break;
		case MessageTypes::ImageDeny:
			m_SensorControllerPanel.OnImageDeny(message);
			break;
		case MessageTypes::ImageStream:
			m_SensorControllerPanel.OnImageStream(message);
			break;
		case MessageTypes::ImageStreamDeny:
			m_SensorControllerPanel.OnImageStreamDeny(message);
			break;

		// TODO: Implement.
		// Initialization parameter update messages.
		case MessageTypes::InitParametersAccept:
			break;
		case MessageTypes::InitParametersDeny:
			break;

		// TODO: Implement.
		// Recording parameter update messages.
		case MessageTypes::RecordingParametersAccept:
			break;
		case MessageTypes::RecordingParametersDeny:
			break;

		// TODO: Implement.
		// Runtime parameter update messages.
		case MessageTypes::RuntimeParametersAccept:
			break;
		case MessageTypes::RuntimeParametersDeny:
			break;

		// TODO: Implement.
		// Video setting messages.
		case MessageTypes::VideoSettingsRequest:
			break;
		case MessageTypes::VideoSettings:
			break;
	}
}

}}
