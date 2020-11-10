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
	m_CheckerboardTexture = Sennet::Texture2D::Create(
		"../../extern/sennet/assets/textures/Checkerboard-600x600.png");

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
	Sennet::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 
		{ 0.8f, 0.2f, 0.3f, 1.0f });
	Sennet::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, 
		{ 0.2f, 0.3f, 0.8f, 1.0f });
	Sennet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, 
		m_CheckerboardTexture);	
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

		// Settings

		// Image

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
	}
}

}}
