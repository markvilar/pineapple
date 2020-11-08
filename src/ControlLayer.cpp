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
}

void ControlLayer::OnDetach()
{
}

void ControlLayer::OnUpdate(Timestep ts)
{
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
}

void ControlLayer::OnEvent(Event& e)
{
	m_CameraController.OnEvent(e);
}

}}
