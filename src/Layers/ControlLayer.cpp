#include <SennetZED/Layers/ControlLayer.hpp>

#include <imgui.h>

namespace Sennet
{

namespace ZED
{

ControlLayer::ControlLayer()
	: Layer("Information"), 
	m_ConnectionAddress("127.0.0.1"),
	m_ConnectionPort(6000)
{
}

ControlLayer::~ControlLayer()
{
}

void ControlLayer::OnAttach()
{
}

void ControlLayer::OnDetach()
{
}

void ControlLayer::OnUpdate(Timestep ts)
{
	RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	RenderCommand::Clear();
}

void ControlLayer::OnImGuiRender()
{
	static bool settingsMenuBarActive = true;
	ImGui::Begin("Settings", &settingsMenuBarActive, 
		ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open...", "Ctrl+O")) {}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {}
			if (ImGui::MenuItem("Close", "Ctrl+W")) 
			{
				settingsMenuBarActive = false;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Text("Initialization parameters:");
	ImGui::Separator();
	ImGui::Text("Recording parameters:");
	ImGui::Separator();
	ImGui::Text("Runtime parameters:");
	ImGui::Separator();

	static char addressBuffer[20];
	static int portBuffer;
	ImGui::InputText("Address", addressBuffer, IM_ARRAYSIZE(addressBuffer));
	ImGui::InputInt("Port", &portBuffer);
	if(ImGui::Button("Connect"))
	{
		Connect(addressBuffer, portBuffer);
	}
    	
	ImGui::End();
}

void ControlLayer::OnEvent(Event& event)
{
}

void ControlLayer::OnMessage(Ref<Message> msg)
{
	MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<CommandResponse>(
		std::bind(&ControlLayer::OnCommandResponse, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<SettingsResponse>(
		std::bind(&ControlLayer::OnSettingsResponse, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<StateResponse>(
		std::bind(&ControlLayer::OnStateResponse, this, 
		std::placeholders::_1));
}

bool ControlLayer::OnCommandResponse(Ref<CommandResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

bool ControlLayer::OnSettingsResponse(Ref<SettingsResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

bool ControlLayer::OnStateResponse(Ref<StateResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

}
}
