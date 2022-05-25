#pragma once

#ifdef PINEAPPLE_ENABLE_ZED

#include <Pine/Pine.hpp>

#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"
#include "pineapple/zed/types.hpp"

#include "pineapple/zed/camera_manager.hpp"

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
    void UpdatePanelLayouts();

private:
    Pine::Renderer2D::RendererData m_RendererData2D{};
    Pine::OrthographicCameraController m_CameraController;

    std::shared_ptr<Pine::Framebuffer> m_Framebuffer;
    std::shared_ptr<Pine::Texture2D> m_ImageTexture;

    Zed::RecordManager m_RecordManager{};
    Zed::CameraParameters m_CameraParameters{};
    Zed::CameraSettings m_CameraSettings{};
    Zed::ImageSpecification m_ImageSpecs{};

    StaticSeries<float, 400> m_Pressure;
    StaticSeries<float, 400> m_TemperatureLeft;
    StaticSeries<float, 400> m_TemperatureRight;

    StaticSeries<float, 400> m_AccX;
    StaticSeries<float, 400> m_AccY;
    StaticSeries<float, 400> m_AccZ;

    StaticSeries<float, 400> m_AngX;
    StaticSeries<float, 400> m_AngY;
    StaticSeries<float, 400> m_AngZ;

    bool m_ViewportFocused = false;
    bool m_ViewportHovered = false;

    std::unordered_map<const char*, PanelLayout> m_PanelLayouts{};
};

} // namespace Pineapple

#endif // PINEAPPLE_ENABLE_ZED

