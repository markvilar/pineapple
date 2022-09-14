#pragma once

#include <msgpack.hpp>

#include <pine/pine.hpp>

#include "pineapple/common.hpp"
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
    void send_settings(const zed::CameraSettings& settings) const;
    //void send_stream_config();

    template <typename T>
    void send_message(const T& message) const
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
    pine::QuadRenderData quad_data{};
    pine::OrthographicCameraController camera_controller;
    std::shared_ptr<pine::Framebuffer> framebuffer;
    std::shared_ptr<pine::Texture2D> image_texture;
    pine::Image m_image{};

    // Networking entities
    pine::ClientState client;

    // Stream parameters
    StreamConfig stream_config;

    // Camera primitives - local and remote
    zed::CameraParameters camera_parameters = {};
    zed::CameraParameters remote_parameters = {};
    zed::CameraSettings camera_settings = {};
    zed::CameraSettings remote_settings = {};

    // Reference primitives - for automated updates
    zed::CameraSettings reference_settings = {};

    // GUI
    pine::gui::PanelState viewport_panel{};
};

} // namespace pineapple
