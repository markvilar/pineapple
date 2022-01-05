#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/Panels/ClientPanel.hpp"
#include "Pineapple/Panels/InitParametersPanel.hpp"
#include "Pineapple/Panels/RecordingParametersPanel.hpp"
#include "Pineapple/Panels/RuntimeParametersPanel.hpp"
#include "Pineapple/Panels/SensorControllerPanel.hpp"

namespace Pineapple
{

class ControlLayer : public Pine::Layer
{
public:
    ControlLayer();
    ~ControlLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Pine::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Pine::Event& e) override;

private:
    void OnMessage(Pine::TCP::Message<MessageTypes>& message);

private:
    // Rendering
    Pine::OrthographicCameraController m_CameraController;
    Pine::Ref<Pine::Framebuffer> m_Framebuffer;

    // Network
    Pine::Ref<Client> m_Client;

    // Panels
    ClientPanel m_ClientPanel;
    InitParametersPanel m_InitParametersPanel;
    RecordingParametersPanel m_RecordingParametersPanel;
    RuntimeParametersPanel m_RuntimeParametersPanel;
    SensorControllerPanel m_SensorControllerPanel;

    // Viewport
    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    Pine::Vec2 m_ViewportSize = {0.0f, 0.0f};
};

} // namespace Pineapple
