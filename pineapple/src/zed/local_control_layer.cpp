#include "pineapple/zed/local_control_layer.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace pineapple
{

LocalControlLayer::LocalControlLayer()
    : Layer("LocalControlLayer"), m_camera_controller(1.0f),
      m_record_manager(Pine::FileSystem::GetWorkingDirectory())
{
}

LocalControlLayer::~LocalControlLayer() {}

void LocalControlLayer::OnAttach()
{
    UpdatePanelLayouts();

    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    Pine::Framebuffer::Specification framebufferSpecs;
    framebufferSpecs.Width = m_panel_layouts["Viewport"].size.x;
    framebufferSpecs.Height = m_panel_layouts["Viewport"].size.y;
    m_framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_renderer_data = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void LocalControlLayer::OnDetach() {}

void LocalControlLayer::OnUpdate(Pine::Timestep ts)
{
    const auto image_request =
        m_record_manager.request_image(m_image_specs.width,
            m_image_specs.height,
            m_image_specs.view);
    if (image_request.has_value())
    {
        const auto& image = image_request.value();
        m_image_texture = Pine::Texture2D::Create(convert_image(image));
    }

    const auto sensor_data_request = m_record_manager.request_sensor_data();
    if (sensor_data_request.has_value())
    {
        const auto& data = sensor_data_request.value();

        m_pressure.push_back(data.pressure);
        m_temperature_left.push_back(data.temperature_left);
        m_temperature_right.push_back(data.temperature_right);

        m_acc_x.push_back(data.acceleration.x);
        m_acc_y.push_back(data.acceleration.y);
        m_acc_z.push_back(data.acceleration.z);

        m_ang_x.push_back(data.angular_velocity.x);
        m_ang_y.push_back(data.angular_velocity.y);
        m_ang_z.push_back(data.angular_velocity.z);
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

    Pine::RenderCommand::SetClearColor({0.10f, 0.10f, 0.10f, 1.00f});
    Pine::RenderCommand::Clear();

    m_framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
    Pine::RenderCommand::Clear();

    Pine::Renderer2D::BeginScene(m_renderer_data,
        m_camera_controller.GetCamera());

    if (m_image_texture)
    {
        Pine::Renderer2D::DrawQuad(m_renderer_data,
            {0.0f, 0.0f, 0.0f},
            {(m_image_specs.width / 1000.0f),
                -(m_image_specs.height / 1000.0f)},
            m_image_texture,
            1.0f,
            Pine::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
    }

    Pine::Renderer2D::EndScene(m_renderer_data);

    m_framebuffer->Unbind();
}

void LocalControlLayer::OnImGuiRender()
{
    UpdatePanelLayouts();

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
            if (ImGui::Button("Start record"))
            {
                m_record_manager.start_record(m_camera_parameters);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
                m_record_manager.stop_record();
            }

            ImGui::Separator();

            ImGui::Text("Opened:          %d", m_record_manager.is_opened());
            ImGui::Text("Recording:       %d", m_record_manager.is_recording());
            ImGui::Text("Stopped:         %d", m_record_manager.is_stopped());

            ImGui::Text("Space total:     %.2f GB",
                m_record_manager.get_total_space() / 1e9);
            ImGui::Text("Space free:      %.2f GB",
                m_record_manager.get_free_space() / 1e9);
            ImGui::Text("Space available: %.2f GB",
                m_record_manager.get_available_space() / 1e9);

            ImGui::Separator();
            draw_camera_parameters(m_camera_parameters);
            ImGui::Separator();
            draw_camera_settings(m_camera_settings);

            if (ImGui::Button("Request settings"))
            {
                const auto settings_request =
                    m_record_manager.request_camera_settings();
                if (settings_request.has_value())
                {
                    const auto settings = settings_request.value();
                    PINE_INFO("Camera settings:");
                    PINE_INFO(" - Brightness:  {0}", settings.brightness);
                    PINE_INFO(" - Contrast:    {0}", settings.contrast);
                    PINE_INFO(" - Hue:         {0}", settings.hue);
                    PINE_INFO(" - Saturation:  {0}", settings.saturation);
                    PINE_INFO(" - Sharpness:   {0}", settings.sharpness);
                    PINE_INFO(" - Gain:        {0}", settings.gain);
                    PINE_INFO(" - Exposure:    {0}", settings.exposure);
                    PINE_INFO(" - Whiteb.:     {0}", settings.whitebalance);
                    PINE_INFO(" - Auto expos.: {0}", settings.auto_exposure);
                    PINE_INFO(" - Auto w.b.:   {0}",
                        settings.auto_whitebalance);
                    PINE_INFO(" - Enable LED:  {0}", settings.enable_led);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
                m_record_manager.update_camera_settings(m_camera_settings);
            }

            ImGui::Separator();

            draw_image_specification(m_image_specs);
        });

    Pine::UI::AddWindow("Sensor Data",
        m_panel_layouts["RightPanel"].position,
        m_panel_layouts["RightPanel"].size,
        [this]()
        {
            const auto panel_width = m_panel_layouts["RightPanel"].size.x;
            const auto panel_height = m_panel_layouts["RightPanel"].size.y;

            ImGui::PlotLines("Acc. X",
                m_acc_x.data(),
                m_acc_x.size(),
                m_acc_x.offset(),
                "Acceleration X",
                -10.0f,
                10.0f,
                ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Acc. Y",
                m_acc_y.data(),
                m_acc_y.size(),
                m_acc_y.offset(),
                "Acceleration Y",
                -10.0f,
                10.0f,
                ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Acc. Z",
                m_acc_z.data(),
                m_acc_z.size(),
                m_acc_z.offset(),
                "Acceleration Z",
                -10.0f,
                10.0f,
                ImVec2(panel_width, 80.0f));

            Pine::UI::AddEmptySpace(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Ang. vel. X",
                m_ang_x.data(),
                m_ang_x.size(),
                m_ang_x.offset(),
                "Angular velocity X",
                -30.0f,
                30.0f,
                ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Ang. vel. Y",
                m_ang_y.data(),
                m_ang_y.size(),
                m_ang_y.offset(),
                "Angular velocity Y",
                -30.0f,
                30.0f,
                ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Ang. vel. Z",
                m_ang_z.data(),
                m_ang_z.size(),
                m_ang_z.offset(),
                "Angular velocity Z",
                -30.0f,
                30.0f,
                ImVec2(panel_width, 80.0f));

            Pine::UI::AddEmptySpace(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Pressure",
                m_pressure.data(),
                m_pressure.size(),
                m_pressure.offset(),
                "Pressure",
                0.0f,
                100000.0f,
                ImVec2(panel_width, 80.0f));

            ImGui::PlotLines("Temp. left",
                m_temperature_left.data(),
                m_temperature_left.size(),
                m_temperature_left.offset(),
                "Temp. left",
                0.0f,
                40.0f,
                ImVec2(panel_width, 80.0f));

            ImGui::PlotLines("Temp. right",
                m_temperature_right.data(),
                m_temperature_right.size(),
                m_temperature_right.offset(),
                "Temp. right",
                0.0f,
                40.0f,
                ImVec2(panel_width, 80.0f));
        });

    Pine::UI::AddWindow("Console",
        m_panel_layouts["BottomPanel"].position,
        m_panel_layouts["BottomPanel"].size,
        []()
        {
            // TODO: Implement functionality.
        });
}

void LocalControlLayer::OnEvent(Pine::Event& e)
{
    m_camera_controller.OnEvent(e);
}

void LocalControlLayer::UpdatePanelLayouts()
{
    const auto& [window_width, window_height] =
        Pine::Application::Get().GetWindow().GetSize();

    static constexpr auto menu_height = 20.0f;

    const auto& main_menu_layout = m_panel_layouts["MainMenu"];

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

#endif // PINEAPPLE_ENABLE_ZED
