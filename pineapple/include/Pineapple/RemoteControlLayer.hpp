#pragma once

#include <Pine/Pine.hpp>

#include "Pineapple/CameraControls.hpp"
#include "Pineapple/UserInterface.hpp"
#include "Pineapple/Utils.hpp"

namespace Pineapple
{

class RemoteControlLayer : public Pine::Layer
{
public:
    RemoteControlLayer();
    ~RemoteControlLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Pine::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Pine::Event& e) override;

private:
    void OnMessage(const Pine::Message& message);

private:
    Pine::Renderer2D::RendererData m_RendererData{};
    Pine::OrthographicCameraController m_CameraController;

    std::shared_ptr<Pine::Framebuffer> m_Framebuffer;

    //std::unique_ptr<Client> m_Client;

    ZED::CameraParameters m_CameraParameters = {};
    ZED::CameraSettings m_CameraSettings = {};

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    Pine::Vec2 m_ViewportSize = {0.0f, 0.0f};

    std::unordered_map<std::string, PanelLayout> m_PanelLayouts{};
};

} // namespace Pineapple
