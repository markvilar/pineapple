#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"

#include "Sennet/ZED/Panels/ClientPanel.hpp"
#include "Sennet/ZED/Panels/InitParametersPanel.hpp"
#include "Sennet/ZED/Panels/RecordingParametersPanel.hpp"
#include "Sennet/ZED/Panels/RuntimeParametersPanel.hpp"
#include "Sennet/ZED/Panels/SensorControllerPanel.hpp"

namespace Sennet { namespace ZED {

class ControlLayer : public Sennet::Layer
{
public:
	ControlLayer();
	~ControlLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& e) override;

private:
	void OnMessage(Message<MessageTypes>& message);

private:
	// Rendering
	OrthographicCameraController m_CameraController;

	// Network
	Ref<Client> m_Client;

	// Panels
	ClientPanel m_ClientPanel;
	InitParametersPanel m_InitParametersPanel;
	RecordingParametersPanel m_RecordingParametersPanel;
	RuntimeParametersPanel m_RuntimeParametersPanel;
	SensorControllerPanel m_SensorControllerPanel;

};

}}
