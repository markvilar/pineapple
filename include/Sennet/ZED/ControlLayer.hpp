#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/InitParameters.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"

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
	// Graphics
	OrthographicCameraController m_CameraController;
	Ref<Texture2D> m_CheckerboardTexture;

	// Network
	Client<MessageTypes> m_Client;

	Ref<InitParameters> m_InitParameters;
	Ref<RecordingParameters> m_RecordingParameters;
	Ref<RuntimeParameters> m_RuntimeParameters;
};

}}
