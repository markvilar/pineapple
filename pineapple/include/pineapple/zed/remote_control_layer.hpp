#pragma once

#include <msgpack.hpp>

#include <pine/pine.hpp>

#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

namespace pineapple
{

class RemoteControlLayer : public pine::Layer
{
public:
    RemoteControlLayer();
    ~RemoteControlLayer();

    virtual void on_attach() override;
    virtual void on_detach() override;
    virtual void on_update(pine::Timestep ts) override;
    virtual void on_gui_render() override;
    virtual void on_event(pine::Event& e) override;

private:
    void on_message(const std::vector<uint8_t>& buffer) {}

    void send_request(const zed::ControlRequest& request);

    // Debug
    void on_server_message(const std::vector<uint8_t>& buffer);

private:
    // Rendering entities
    pine::QuadRenderData m_renderer_data{};
    pine::OrthographicCameraController m_camera_controller;
    std::shared_ptr<pine::Framebuffer> m_framebuffer;
    std::shared_ptr<pine::Texture2D> m_image_texture;
    pine::Image m_image{};

    // Networking entities
    pine::ClientState client;

    // ZED types, TODO: Replace with the above requests
    zed::CameraParameters camera_parameters = {};
    zed::CameraSettings m_camera_settings = {};
    zed::ImageSpecification m_image_specs{};
    zed::MemoryState m_server_memory{};
    zed::SensorData m_server_sensors{};

    // Data entities
    StaticSeries<float, 400> m_acceleration_x{};
    StaticSeries<float, 400> m_acceleration_y{};
    StaticSeries<float, 400> m_acceleration_z{};
    StaticSeries<float, 400> m_turnrate_x{};
    StaticSeries<float, 400> m_turnrate_y{};
    StaticSeries<float, 400> m_turnrate_z{};

    bool m_viewport_focused = false;
    bool m_viewport_hovered = false;

    // DEBUG
    pine::ServerState server{6000};
};

} // namespace pineapple
