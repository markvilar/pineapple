#pragma once

#include <Pine/Pine.hpp>

#include "pineapple/serialization.hpp"
#include "pineapple/ui_helpers.hpp"
#include "pineapple/utils.hpp"

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

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
    void update_panel_layouts();

    void on_response(const zed::ControlService::Response::DataType& response);
    void on_response(const zed::ImageService::Response::DataType& response);
    void on_response(const zed::MemoryService::Response::DataType& response);
    void on_response(const zed::SensorService::Response::DataType& response);
    void on_response(const zed::SettingsService::Response::DataType& response);

private:
    // Rendering entities
    Pine::Renderer2D::RendererData m_renderer_data{};
    Pine::OrthographicCameraController m_camera_controller;
    std::shared_ptr<Pine::Framebuffer> m_framebuffer;
    std::shared_ptr<Pine::Texture2D> m_image_texture;
    Pine::Image m_image{};

    // Networking entities
    Pine::ClientState m_client;

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

    std::unordered_map<std::string, PanelLayout> m_panel_layouts{};
};

} // namespace pineapple
