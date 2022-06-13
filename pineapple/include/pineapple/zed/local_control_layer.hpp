#pragma once

#ifdef PINEAPPLE_ENABLE_ZED

#include <Pine/Pine.hpp>

#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"
#include "pineapple/zed/types.hpp"

#include "pineapple/zed/camera_manager.hpp"

namespace pineapple
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
    Pine::Renderer2D::RendererData m_renderer_data{};
    Pine::OrthographicCameraController m_camera_controller;

    std::shared_ptr<Pine::Framebuffer> m_framebuffer;
    std::shared_ptr<Pine::Texture2D> m_image_texture;

    zed::RecordManager m_record_manager{};
    zed::CameraParameters m_camera_parameters{};
    zed::CameraSettings m_camera_settings{};
    zed::ImageSpecification m_image_specs{};

    StaticSeries<float, 400> m_pressure;
    StaticSeries<float, 400> m_temperature_left;
    StaticSeries<float, 400> m_temperature_right;

    StaticSeries<float, 400> m_acc_x;
    StaticSeries<float, 400> m_acc_y;
    StaticSeries<float, 400> m_acc_z;

    StaticSeries<float, 400> m_ang_x;
    StaticSeries<float, 400> m_ang_y;
    StaticSeries<float, 400> m_ang_z;

    bool m_viewport_focused = false;
    bool m_viewport_hovered = false;

    std::unordered_map<const char*, PanelLayout> m_panel_layouts{};
};

} // namespace pineapple

#endif // PINEAPPLE_ENABLE_ZED
