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
}

void RemoteControlLayer::on_detach() {}

void RemoteControlLayer::on_update(pine::Timestep ts)
{
    while (!m_client.message_queue.empty())
    {
        const auto& message = m_client.message_queue.pop_front();
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
            ImGui::Text("Client connected: %d", is_connected(m_client));

            if (ImGui::Button("Connect", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::connect(m_client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect", 
                ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::disconnect(m_client);
            }

            ImGui::Separator();

            // ----------------------------------------------------------------
            // Camera controls
            // ----------------------------------------------------------------

            if (ImGui::Button("Record", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                if (pine::is_connected(m_client))
                {
                    zed::ControlService::Request request;
                    request.header = zed::ServiceIdentifier::CONTROL_REQUEST;
                    request.data.action = zed::CameraAction::START_RECORD;
                    request.data.resolution = m_camera_parameters.resolution;
                    request.data.compression = m_camera_parameters.compression;
                    request.data.fps = m_camera_parameters.fps;
                    request.data.timeout = m_camera_parameters.timeout;
                    request.data.enable_image_enhancement 
                        = m_camera_parameters.enable_image_enhancement;
                    request.data.disable_self_calibration 
                        = m_camera_parameters.disable_self_calibration;
                    request.data.require_sensors 
                        = m_camera_parameters.require_sensors;
                    request.data.enable_depth
                        = m_camera_parameters.enable_depth;

                    MemoryOutputArchive output_archive;
                    output_archive.serialize(request);

                    pine::send(m_client, output_archive.get_buffer().data(), 
                        output_archive.get_buffer().size());
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                if (pine::is_connected(m_client))
                {
                    zed::ControlService::Request request;
                    request.header = zed::ServiceIdentifier::CONTROL_REQUEST;
                    request.data.action = zed::CameraAction::STOP_RECORD;

                    MemoryOutputArchive output_archive;
                    output_archive.serialize(request);

                    pine::send(m_client, output_archive.get_buffer().data(), 
                        output_archive.get_buffer().size());
                }
            }

            ImGui::Separator();
            draw_camera_parameters(m_camera_parameters);
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
}

void RemoteControlLayer::on_event(pine::Event& e)
{
    m_camera_controller.on_event(e);
}

void RemoteControlLayer::on_response(
    const zed::ControlService::Response::DataType& response)
{
    // TODO: Implement.
    PINE_INFO("Remote control: Got control response.");
}

void RemoteControlLayer::on_response(
    const zed::ImageService::Response::DataType& response)
{
    PINE_INFO("Remote control: Got image response.");

    // TODO: Perform sanity check

    const auto format = [&response]()
        {
            switch (response.view)
            {
            case zed::View::LEFT:
                return pine::ImageFormat::BGRA;
            case zed::View::RIGHT:
                return pine::ImageFormat::BGRA;
            case zed::View::LEFT_GRAY:
                return pine::ImageFormat::GRAY;
            case zed::View::RIGHT_GRAY:
                return pine::ImageFormat::GRAY;
            case zed::View::SIDE_BY_SIDE:
                return pine::ImageFormat::BGRA;
            default:
                return pine::ImageFormat::GRAY;
            };
        }();

    m_image = pine::Image(response.buffer.data(), response.width, 
        response.height, format);
}

void RemoteControlLayer::on_response(
    const zed::MemoryService::Response::DataType& response)
{
    PINE_INFO("Remote control: Got memory response.");
    m_server_memory.total_space = response.total_space;
    m_server_memory.free_space = response.free_space;
    m_server_memory.available_space = response.available_space;
}

void RemoteControlLayer::on_response(
    const zed::SensorService::Response::DataType& response)
{
    PINE_INFO("Remote control: Got sensor response.");
    PINE_INFO(" - Acceleration: {0}, {1}, {2}", response.acceleration.x,
        response.acceleration.y, response.acceleration.z);
    PINE_INFO(" - Turnrate:     {0}, {1}, {2}", response.turnrate.x,
        response.turnrate.y, response.turnrate.z);

    m_server_sensors.acceleration.x = response.acceleration.x;
    m_server_sensors.acceleration.y = response.acceleration.y;
    m_server_sensors.acceleration.z = response.acceleration.z;

    m_server_sensors.turnrate.x = response.turnrate.x;
    m_server_sensors.turnrate.y = response.turnrate.y;
    m_server_sensors.turnrate.z = response.turnrate.z;

    m_acceleration_x.push_back(response.acceleration.x);
    m_acceleration_y.push_back(response.acceleration.y);
    m_acceleration_z.push_back(response.acceleration.z);

    m_turnrate_x.push_back(response.turnrate.x);
    m_turnrate_y.push_back(response.turnrate.y);
    m_turnrate_z.push_back(response.turnrate.z);
}

void RemoteControlLayer::on_response(
    const zed::SettingsService::Response::DataType& response)
{
    PINE_INFO("Remote control: Got settings response.");
    m_camera_settings.brightness = response.brightness;
    m_camera_settings.contrast = response.contrast;
    m_camera_settings.hue = response.hue;
    m_camera_settings.saturation = response.saturation;
    m_camera_settings.sharpness = response.sharpness;
    m_camera_settings.gamma = response.gamma;
    m_camera_settings.gain = response.gain;
    m_camera_settings.exposure = response.exposure;
    m_camera_settings.whitebalance = response.whitebalance;
    m_camera_settings.auto_exposure = response.auto_exposure;
    m_camera_settings.auto_whitebalance = response.auto_whitebalance;
    m_camera_settings.enable_led = response.enable_led;
}

}; // namespace pineapple
