#include "pineapple/zed/remote_control_layer.hpp"

namespace pineapple
{

RemoteControlLayer::RemoteControlLayer()
    : Layer("RemoteControlLayer"), m_camera_controller(1.0f)
{
}

RemoteControlLayer::~RemoteControlLayer() {}

void RemoteControlLayer::OnAttach()
{
    update_panel_layouts();

    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    Pine::Framebuffer::Specification framebufferSpecs;
    framebufferSpecs.Width = 1280;
    framebufferSpecs.Height = 720;
    m_framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_renderer_data = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void RemoteControlLayer::OnDetach() {}

void RemoteControlLayer::OnUpdate(Pine::Timestep ts)
{
    while (!m_client.message_queue.empty())
    {
        const auto& message = m_client.message_queue.pop_front();
        // TODO: Handle message
    }

    const auto specs = m_framebuffer->GetSpecification();
    const auto viewport = m_panel_layouts["Viewport"];

    if (viewport.size.x > 0.0f && viewport.size.y > 0.0f
        && (specs.Width != viewport.size.x || specs.Height != viewport.size.y))
    {
        m_framebuffer->Resize(viewport.size.x, viewport.size.y);
        m_camera_controller.OnResize(viewport.size.x, viewport.size.y);
    }

    if (m_viewport_focused)
        m_camera_controller.OnUpdate(ts);

    m_image_texture = Pine::Texture2D::Create(m_image);

    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    m_framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    Pine::Renderer2D::BeginScene(m_renderer_data,
        m_camera_controller.GetCamera());

    if (m_image_texture)
    {
        Pine::Renderer2D::DrawQuad(m_renderer_data,
            {0.0f, 0.0f, 0.0f},
            {(m_image.Width / 1000.0f), -(m_image.Height / 1000.0f)},
            m_image_texture,
            1.0f,
            Pine::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
    }

    Pine::Renderer2D::EndScene(m_renderer_data);
    m_framebuffer->Unbind();
}

void RemoteControlLayer::OnImGuiRender()
{
    update_panel_layouts();

    Pine::UI::AddMainMenuBar(
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
                    Pine::Application::Get().Close();
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

    Pine::UI::AddViewport("Viewport",
        m_panel_layouts["Viewport"].position,
        m_panel_layouts["Viewport"].size,
        *m_framebuffer.get(),
        [this]()
        {
            m_viewport_focused = ImGui::IsWindowFocused();
            m_viewport_hovered = ImGui::IsWindowHovered();
            Pine::Application::Get().GetImGuiLayer()->BlockEvents(
                !m_viewport_focused || !m_viewport_hovered);
        });

    Pine::UI::AddWindow("Camera Controls",
        m_panel_layouts["LeftPanel"].position,
        m_panel_layouts["LeftPanel"].size,
        [this]()
        {
            static char address[256] = "";
            static uint16_t port = 0;

            static constexpr auto control_panel_height = 200;
            const auto content_size = ImGui::GetContentRegionAvail();

            ImGui::InputText("Server Address", address, IM_ARRAYSIZE(address));
            ImGui::InputInt("Server Port", (int*)&port, 0, 0);
            ImGui::Text("Client connected: %d", IsConnected(m_client));

            if (ImGui::Button("Connect", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                Pine::Connect(m_client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect", 
                ImVec2(0.50f * content_size.x, 30.0f)))
            {
                Pine::Disconnect(m_client);
            }

            ImGui::Separator();

            // ----------------------------------------------------------------
            // Camera controls
            // ----------------------------------------------------------------

            if (ImGui::Button("Record", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                if (Pine::IsConnected(m_client))
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

                    Pine::Send(m_client, output_archive.get_buffer().data(), 
                        output_archive.get_buffer().size());
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                if (Pine::IsConnected(m_client))
                {
                    zed::ControlService::Request request;
                    request.header = zed::ServiceIdentifier::CONTROL_REQUEST;
                    request.data.action = zed::CameraAction::STOP_RECORD;

                    MemoryOutputArchive output_archive;
                    output_archive.serialize(request);

                    Pine::Send(m_client, output_archive.get_buffer().data(), 
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

    Pine::UI::AddWindow("Sensor Data",
        m_panel_layouts["RightPanel"].position,
        m_panel_layouts["RightPanel"].size,
        []()
        {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Console",
        m_panel_layouts["BottomPanel"].position,
        m_panel_layouts["BottomPanel"].size,
        []()
        {
            // TODO: Implement functionality.
        });
}

void RemoteControlLayer::OnEvent(Pine::Event& e)
{
    m_camera_controller.OnEvent(e);
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
                return Pine::ImageFormat::BGRA;
            case zed::View::RIGHT:
                return Pine::ImageFormat::BGRA;
            case zed::View::LEFT_GRAY:
                return Pine::ImageFormat::GRAY;
            case zed::View::RIGHT_GRAY:
                return Pine::ImageFormat::GRAY;
            case zed::View::SIDE_BY_SIDE:
                return Pine::ImageFormat::BGRA;
            default:
                return Pine::ImageFormat::GRAY;
            };
        }();

    m_image = Pine::Image(response.buffer.data(), response.width, 
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

void RemoteControlLayer::update_panel_layouts()
{
    const auto& [window_width, window_height] =
        Pine::Application::Get().GetWindow().GetSize();

    static constexpr auto menu_height = 20.0f;

    const auto& mainMenuLayout = m_panel_layouts["MainMenu"];

    m_panel_layouts["LeftPanel"] = PanelLayout(Pine::Vec2(0.0f * window_width,
                                                   0.0f * window_height
                                                       + menu_height),
        Pine::Vec2(0.2f * window_width, 1.0f * window_height - menu_height));

    m_panel_layouts["Viewport"] =
        PanelLayout(Pine::Vec2(0.2f * window_width,
                        0.0f * window_height + menu_height),
            Pine::Vec2(0.6f * window_width, 0.8f * window_height));

    m_panel_layouts["RightPanel"] = PanelLayout(Pine::Vec2(0.8f * window_width,
                                                    0.0f * window_height
                                                        + menu_height),
        Pine::Vec2(0.2f * window_width, 1.0f * window_height - menu_height));

    m_panel_layouts["BottomPanel"] = PanelLayout(Pine::Vec2(0.2f * window_width,
                                                     0.8f * window_height
                                                         + menu_height),
        Pine::Vec2(0.6f * window_width, 0.2f * window_height - menu_height));
}

}; // namespace pineapple
