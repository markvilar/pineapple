#pragma once

#include <Pine/Pine.hpp>

#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"
#include "pineapple/zed/types.hpp"
#include "pineapple/zed/protocol.hpp"

namespace pineapple
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
    void UpdatePanelLayouts();
private:
    Pine::Renderer2D::RendererData m_RendererData{};
    Pine::OrthographicCameraController m_CameraController;

    std::shared_ptr<Pine::Framebuffer> m_Framebuffer;
    std::shared_ptr<Pine::Texture2D> m_ImageTexture;

    Pine::ClientState m_Client;

    zed::ControlRequest m_ControlRequest = {};
    zed::SettingsRequest m_SettingsRequest = {};
    zed::StateRequest m_StateRequest = {};
    zed::SensorRequest m_SensorRequest = {};
    zed::ImageRequest m_ImageRequest = {};

    zed::CameraParameters m_CameraParameters = {};
    zed::CameraSettings m_CameraSettings = {};
    zed::ImageSpecification m_ImageSpecs{};

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;

    std::unordered_map<std::string, PanelLayout> m_PanelLayouts{};
};

} // namespace pineapple
