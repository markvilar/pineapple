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
    template <typename T>
    void send_message(const T& message)
    {
        msgpack::sbuffer buffer;
        msgpack::pack(buffer, message);
        pine::send(client, (uint8_t*)buffer.data(), buffer.size());
    }

    void on_message(const std::vector<uint8_t>& buffer);

    void on_message(const zed::ControlMessage& message);
    void on_message(const zed::SettingsMessage& message);
    void on_message(const zed::SensorMessage& message);
    void on_message(const zed::ImageMessage& message);

private:
    // Rendering entities
    pine::QuadRenderData quad_renderer{};
    pine::OrthographicCameraController camera_controller;
    std::shared_ptr<pine::Framebuffer> framebuffer;
    std::shared_ptr<pine::Texture2D> image_texture;
    pine::Image m_image{};

    // Networking entities
    pine::ClientState client;

    // Stream parameters
    uint16_t image_width = 1280;
    uint16_t image_height = 720;
    float stream_period = 1.0f;

    // ZED types
    zed::CameraParameters camera_parameters = {};
    zed::CameraSettings camera_settings = {};

    // GUI
    pine::gui::PanelState viewport_panel{};
    bool m_viewport_focused = false;
    bool m_viewport_hovered = false;
};

} // namespace pineapple
