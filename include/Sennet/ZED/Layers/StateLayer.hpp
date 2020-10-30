#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages/Request.hpp"
#include "Sennet/ZED/Messages/Response.hpp"

#include "Sennet/ZED/Parameters/InitParameters.hpp"
#include "Sennet/ZED/Parameters/RecordingParameters.hpp"
#include "Sennet/ZED/Parameters/RuntimeParameters.hpp"

namespace Sennet
{

namespace ZED
{

class StateLayer : public Sennet::Layer
{
public:
	StateLayer();
	~StateLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(Event& event) override;
	virtual void OnMessage(Ref<Message> msg) override;

private:
	bool OnStateResponse(Ref<StateResponse> msg);
	void SetupStateRequest();
	void SubmitStateRequest(const std::string address, 
		const unsigned short port);

	void RenderStateWindow();
	void RenderNodeSelectionHeader();
	void RenderNodeStateHeader();
	void RenderNodeStateInitParameters();
	void RenderNodeStateRecordingParameters();
	void RenderNodeStateRuntimeParameters();


	void StartMonitoringNode(const std::string address,
		const std::string port);
	void StopMonitoringNode();

private:
	Sennet::Ref<Sennet::Texture2D> m_ImageTexture;
	Sennet::Ref<Sennet::Shader> m_TextureShader;	
	Sennet::Ref<Sennet::VertexArray> m_SquareVa;

	Sennet::OrthographicCameraController m_CameraController;
	float m_CameraTranslationSpeed = 1.5f;
	float m_CameraRotationSpeed = 70.0f;

	bool m_ShouldMonitor = false;
	std::string m_MonitoringNodeAddress = "";
	std::string m_MonitoringNodePort = "";

	float m_StateRequestFrequency = 30.0f;
	float m_LastStateRequestTime = 0.0f;

	RecorderState m_RecorderState;
	InitParameters m_InitParameters;
	RecordingParameters m_RecordingParameters;
	RuntimeParameters m_RuntimeParameters;
};

}
}
