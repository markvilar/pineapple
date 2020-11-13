#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/RecordClient.hpp"

#include "Sennet/ZED/Panels/InitParametersPanel.hpp"
#include "Sennet/ZED/Panels/RecordClientPanel.hpp"
#include "Sennet/ZED/Panels/RecordingParametersPanel.hpp"
#include "Sennet/ZED/Panels/RuntimeParametersPanel.hpp"

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

	void CreateImageTexture(const std::vector<uint8_t>& data, 
		const uint32_t& width, const uint32_t& height, 
		const uint32_t& channels);
private:
	// Rendering
	OrthographicCameraController m_CameraController;
	Ref<Texture2D> m_CheckerboardTexture;
	Ref<Texture2D> m_ImageTexture;

	// Panels
	RecordClientPanel m_ClientPanel;
	InitParametersPanel m_InitParametersPanel;
	RecordingParametersPanel m_RecordingParametersPanel;
	RuntimeParametersPanel m_RuntimeParametersPanel;

	// Network
	Ref<RecordClient> m_Client;

	// Parameters
	Ref<InitParameters> m_InitParameters;
	Ref<RecordingParameters> m_RecordingParameters;
	Ref<RuntimeParameters> m_RuntimeParameters;
};

}}
