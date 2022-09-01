#pragma once

#include <pine/pine.hpp>

#include "pineapple/serialization.hpp"
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
    void on_response(const zed::ControlService::Response::DataType& response);
    void on_response(const zed::ImageService::Response::DataType& response);
    void on_response(const zed::MemoryService::Response::DataType& response);
    void on_response(const zed::SensorService::Response::DataType& response);
    void on_response(const zed::SettingsService::Response::DataType& response);

private:
    // Rendering entities
    pine::QuadRenderData m_renderer_data{};
    pine::OrthographicCameraController m_camera_controller;
    std::shared_ptr<pine::Framebuffer> m_framebuffer;
    std::shared_ptr<pine::Texture2D> m_image_texture;
    pine::Image m_image{};

    // Networking entities
    pine::ClientState m_client;

    // ZED services
    zed::ControlService::Request m_control_request{};
    zed::ImageService::Request m_image_request{};
    zed::MemoryService::Request m_memory_request{};
    zed::SensorService::Request m_sensor_request{};
    zed::SettingsService::Request m_settings_request{};

    // ZED types, TODO: Replace with the above requests
    zed::CameraParameters m_camera_parameters = {};
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
};

} // namespace pineapple
