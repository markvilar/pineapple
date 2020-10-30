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

class ControlLayer : public Sennet::Layer
{
public:
	ControlLayer();
	~ControlLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(Event& event) override;
	virtual void OnMessage(Ref<Message> msg) override;

private:
	bool OnCommandResponse(Ref<CommandResponse> msg);
	bool OnSettingsResponse(Ref<SettingsResponse> msg);

	void SubmitCommandRequest(const std::string address, 
		const std::string port);
	void SubmitSettingsRequest(const std::string address, 
		const std::string port);

	void RenderControlWindow();

	void RenderCommandHeader();
	void RenderCommandConfigurationNode();
	void RenderCommandSubmissionNode();

	void RenderSettingsHeader();
	void RenderSettingsInitParametersNode();
	void RenderSettingsRecordingParametersNode();
	void RenderSettingsRuntimeParametersNode();
	void RenderSettingsSubmissionNode();

private:
	Command m_Command;
	InitParametersData m_InitData;
	RecordingParametersData m_RecordingData;
	RuntimeParametersData m_RuntimeData;
};

}
}
