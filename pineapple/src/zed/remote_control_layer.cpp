#include "pineapple/zed/remote_control_layer.hpp"

namespace pineapple
{

RemoteControlLayer::RemoteControlLayer()
    : Layer("RemoteControlLayer"), m_camera_controller(1.0f)
{
}

RemoteControlLayer::~RemoteControlLayer() {}

void RemoteControlLayer::on_attach()
{
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    pine::FramebufferSpecs framebuffer_specs;
    framebuffer_specs.width = 1280;
    framebuffer_specs.height = 720;
    m_framebuffer = pine::Framebuffer::create(framebuffer_specs);

    m_renderer_data = pine::QuadRenderer::init();

    pine::gui::set_dark_theme(ImGui::GetStyle());

    // TODO: Debug
    server.set_connection_callback(
        [](const pine::ConnectionState& connection) -> bool
        {
            PINE_INFO("New client: {0}", connection.socket.remote_endpoint());
            return true;
        });

    server.set_message_callback(
        [this](const std::vector<uint8_t>& buffer) -> void
        {
            on_server_message(buffer);
        });

    start_server(server);
}

void RemoteControlLayer::on_detach() {}

void RemoteControlLayer::on_update(pine::Timestep ts)
{
    // TODO: Debug
    update_server(server, 10);

    while (!client.message_queue.empty())
    {
        const auto& message = client.message_queue.pop_front();
        // TODO: Handle message
    }

    /*
    if (m_viewport_focused)
        m_camera_controller.OnUpdate(ts);
    */

    m_image_texture = pine::Texture2D::create(m_image);

    pine::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
    pine::RenderCommand::clear();

    m_framebuffer->bind();
    pine::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
    pine::RenderCommand::clear();

    pine::QuadRenderer::begin_scene(m_renderer_data,
        m_camera_controller.get_camera());

    if (m_image_texture)
    {
        pine::QuadRenderer::draw_quad(m_renderer_data,
            {0.0f, 0.0f, 0.0f},
            {(m_image.get_width() / 1000.0f), -(m_image.get_height() / 1000.0f)},
            m_image_texture,
            1.0f,
            pine::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    pine::QuadRenderer::end_scene(m_renderer_data);
    m_framebuffer->unbind();
}

void RemoteControlLayer::on_gui_render()
{
    pine::gui::render_dockspace("dockspace");
    pine::gui::main_menu_bar(
        []()
        {
            static bool show_imgui_demo = false;
            static bool show_imgui_metrics = false;
            static bool show_imgui_stack = false;

            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                }
                if (ImGui::MenuItem("Exit", "Ctrl+W"))
                {
                    pine::Application::get().close();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("ImGui"))
            {
                ImGui::Checkbox("Show ImGui demo window", &show_imgui_demo);
                ImGui::Checkbox("Show ImGui metrics", &show_imgui_metrics);
                ImGui::Checkbox("Show ImGui stack tool", &show_imgui_stack);
                ImGui::EndMenu();
            }

            if (show_imgui_demo)
                ImGui::ShowDemoWindow();
            if (show_imgui_metrics)
                ImGui::ShowMetricsWindow();
            if (show_imgui_stack)
                ImGui::ShowStackToolWindow();
        });

    const auto viewport_panel = pine::gui::render_viewport("Viewport", 
        *m_framebuffer.get());
    const auto specs = m_framebuffer->get_specification();

    if (viewport_panel.size.x > 0.0f && viewport_panel.size.y > 0.0f
        && (specs.width != viewport_panel.size.x 
        || specs.height != viewport_panel.size.y))
    {
        m_framebuffer->resize(viewport_panel.size.x, viewport_panel.size.y);
        m_camera_controller.on_resize(viewport_panel.size.x, 
            viewport_panel.size.y);
    }

    pine::gui::render_window("Camera Controls",
        [this]()
        {
            static char address[256] = "";
            static uint16_t port = 0;

            static constexpr auto control_panel_height = 200;
            const auto content_size = ImGui::GetContentRegionAvail();

            ImGui::InputText("Server Address", address, IM_ARRAYSIZE(address));
            ImGui::InputInt("Server Port", (int*)&port, 0, 0);
            ImGui::Text("Client connected: %d", is_connected(client));

            if (ImGui::Button("Connect", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::connect(client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect", 
                ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::disconnect(client);
            }

            ImGui::Separator();

            // ----------------------------------------------------------------
            // Camera controls
            // ----------------------------------------------------------------

            if (ImGui::Button("Record", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::ControlRequest request;
                request.topic = "/desktop/control_request";
                request.action = "start_record";
                request.fps = camera_parameters.fps;
                request.timeout = camera_parameters.timeout;
                request.enable_image_enhancement 
                    = camera_parameters.enable_image_enhancement;
                request.disable_self_calibration 
                    = camera_parameters.disable_self_calibration;
                request.require_sensors = camera_parameters.require_sensors;
                request.enable_depth = camera_parameters.enable_depth;

                send_request(request);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record", 
                ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::ControlRequest request;
                request.topic = "/desktop/control_request";
                request.action = "stop_record";
                request.fps = camera_parameters.fps;
                request.timeout = camera_parameters.timeout;
                request.enable_image_enhancement 
                    = camera_parameters.enable_image_enhancement;
                request.disable_self_calibration 
                    = camera_parameters.disable_self_calibration;
                request.require_sensors = camera_parameters.require_sensors;
                request.enable_depth = camera_parameters.enable_depth;

                send_request(request);
            }

            ImGui::Separator();
            draw_camera_parameters(camera_parameters);
            ImGui::Separator();
            draw_camera_settings(m_camera_settings);
            ImGui::Separator();
            draw_image_specification(m_image_specs);
        });

    pine::gui::render_window("Sensor Data",
        []()
        {
            // TODO: Implement functionality.
        });

    pine::gui::render_window("Console",
        []()
        {
            // TODO: Implement functionality.
        });

    pine::gui::render_window("Test message",
        [this]()
        {
        });
}

void RemoteControlLayer::on_event(pine::Event& e)
{
    m_camera_controller.on_event(e);
}

void RemoteControlLayer::send_request(const zed::ControlRequest& request)
{
    msgpack::sbuffer buffer;
    msgpack::pack(buffer, request);

    pine::send(client, (uint8_t*)buffer.data(), buffer.size());

    PINE_INFO("Client sent {0} bytes", buffer.size());
}

// TODO: Remove, debug
void RemoteControlLayer::on_server_message(const std::vector<uint8_t>& buffer)
{
    PINE_INFO("Server got {0} bytes", buffer.size());

    msgpack::object_handle handle 
        = msgpack::unpack((char*)buffer.data(), buffer.size());
    msgpack::object object = handle.get();

    PINE_INFO("Object: {0}", object);
}

}; // namespace pineapple
