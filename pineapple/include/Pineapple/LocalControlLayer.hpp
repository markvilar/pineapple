#pragma once

#include <Pine/Pine.hpp>

#include "Pineapple/CameraInterface.hpp"
#include "Pineapple/CameraParameters.hpp"
#include "Pineapple/CameraSettings.hpp"
#include "Pineapple/Client.hpp"
#include "Pineapple/Utils.hpp"

namespace Pineapple
{

class LocalControlLayer : public Pine::Layer
{
public:
    LocalControlLayer();
    ~LocalControlLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Pine::Timestep ts) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Pine::Event& e) override;

private:
    Pine::OrthographicCameraController m_CameraController;
    std::shared_ptr<Pine::Framebuffer> m_Framebuffer;

    ZED::CameraInterface m_CameraInterface = {};
    ZED::CameraParameters m_CameraParameters = {};
    ZED::CameraSettings m_CameraSettings = {};

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;
    Pine::Vec2 m_ViewportSize = {0.0f, 0.0f};
};

} // namespace Pineapple
