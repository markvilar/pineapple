#pragma once

#ifdef PINEAPPLE_ENABLE_ZED

#include <pine/pine.hpp>

#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"
#include "pineapple/zed/types.hpp"

#include "pineapple/zed/camera_manager.hpp"

namespace pineapple
{

class LocalControlLayer : public pine::Layer
{
public:
    LocalControlLayer();
    ~LocalControlLayer();

    virtual void on_attach() override;
    virtual void on_detach() override;
    virtual void on_update(const pine::Timestep& ts) override;
    virtual void on_gui_render() override;
    virtual void on_event(pine::Event& e) override;

private:
    pine::QuadRenderData m_renderer_data{};
    pine::OrthographicCameraController m_camera_controller;

    std::shared_ptr<pine::Framebuffer> m_framebuffer;
    std::shared_ptr<pine::Texture2D> m_image_texture;

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
};

} // namespace pineapple

#endif // PINEAPPLE_ENABLE_ZED
