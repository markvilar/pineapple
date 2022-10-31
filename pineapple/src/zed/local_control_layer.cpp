#include "pineapple/zed/local_control_layer.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace pineapple
{

LocalControlLayer::LocalControlLayer()
    : Layer("LocalControlLayer"), m_camera_controller(1.0f),
      m_record_manager(pine::filesystem::get_working_directory())
{
}

LocalControlLayer::~LocalControlLayer() {}

void LocalControlLayer::on_attach()
{
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    pine::FramebufferSpecs framebuffer_specs;
    framebuffer_specs.width = 0;
    framebuffer_specs.height = 0;
    m_framebuffer = pine::Framebuffer::create(framebuffer_specs);

    m_renderer_data = pine::QuadRenderer::init();

    pine::gui::set_dark_theme(ImGui::GetStyle());
}

void LocalControlLayer::on_detach() {}

void LocalControlLayer::on_update(pine::Timestep ts)
{
    const auto image_request =
        m_record_manager.get_image(m_image_specs.width, m_image_specs.height);
    if (image_request.has_value())
    {
        const auto& image = image_request.value();
        // FIXME: m_image_texture =
        // pine::Texture2D::create(convert_image(image));
    }

    const auto sensor_data_request = m_record_manager.get_sensor_data();
    if (sensor_data_request.has_value())
    {
        const auto& data = sensor_data_request.value();

        m_pressure.push_back(data.pressure);
        m_temperature_left.push_back(data.temperature_left);
        m_temperature_right.push_back(data.temperature_right);

        m_acc_x.push_back(data.acceleration.x);
        m_acc_y.push_back(data.acceleration.y);
        m_acc_z.push_back(data.acceleration.z);

        m_ang_x.push_back(data.turnrate.x);
        m_ang_y.push_back(data.turnrate.y);
        m_ang_z.push_back(data.turnrate.z);
    }

    /*
    if (m_viewport_focused)
        m_camera_controller.on_update(ts);
    */

    pine::RenderCommand::set_clear_color({0.10f, 0.10f, 0.10f, 1.00f});
    pine::RenderCommand::clear();

    m_framebuffer->bind();
    pine::RenderCommand::set_clear_color({0.15f, 0.15f, 0.15f, 1.00f});
    pine::RenderCommand::clear();

    pine::QuadRenderer::begin_scene(m_renderer_data,
        m_camera_controller.get_camera());

    if (m_image_texture)
    {
        pine::QuadRenderer::draw_quad(m_renderer_data,
            {0.0f, 0.0f, 0.0f},
            {(m_image_specs.width / 1000.0f),
                -(m_image_specs.height / 1000.0f)},
            m_image_texture,
            1.0f,
            pine::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
    }

    pine::QuadRenderer::end_scene(m_renderer_data);

    m_framebuffer->unbind();
}

void LocalControlLayer::on_gui_render()
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

    const auto viewport_panel =
        pine::gui::render_viewport("Viewport", *m_framebuffer.get());
    const auto& specs = m_framebuffer->get_specification();

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
                const auto settings_request = m_record_manager.get_settings();
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
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
                m_record_manager.update_settings(m_camera_settings);
            }

            ImGui::Separator();

            draw_image_specification(m_image_specs);
        });

    pine::gui::render_window("Sensor Data",
        [this]()
        {
            const auto width = 160.0f;

            ImGui::PlotLines("Acc. X",
                m_acc_x.data(),
                m_acc_x.size(),
                m_acc_x.offset(),
                "Acceleration X",
                -10.0f,
                10.0f,
                ImVec2(width, 80.0f));
            ImGui::PlotLines("Acc. Y",
                m_acc_y.data(),
                m_acc_y.size(),
                m_acc_y.offset(),
                "Acceleration Y",
                -10.0f,
                10.0f,
                ImVec2(width, 80.0f));
            ImGui::PlotLines("Acc. Z",
                m_acc_z.data(),
                m_acc_z.size(),
                m_acc_z.offset(),
                "Acceleration Z",
                -10.0f,
                10.0f,
                ImVec2(width, 80.0f));

            pine::gui::empty_space(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Ang. vel. X",
                m_ang_x.data(),
                m_ang_x.size(),
                m_ang_x.offset(),
                "Angular velocity X",
                -30.0f,
                30.0f,
                ImVec2(width, 80.0f));
            ImGui::PlotLines("Ang. vel. Y",
                m_ang_y.data(),
                m_ang_y.size(),
                m_ang_y.offset(),
                "Angular velocity Y",
                -30.0f,
                30.0f,
                ImVec2(width, 80.0f));
            ImGui::PlotLines("Ang. vel. Z",
                m_ang_z.data(),
                m_ang_z.size(),
                m_ang_z.offset(),
                "Angular velocity Z",
                -30.0f,
                30.0f,
                ImVec2(width, 80.0f));

            pine::gui::empty_space(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Pressure",
                m_pressure.data(),
                m_pressure.size(),
                m_pressure.offset(),
                "Pressure",
                0.0f,
                100000.0f,
                ImVec2(width, 80.0f));

            ImGui::PlotLines("Temp. left",
                m_temperature_left.data(),
                m_temperature_left.size(),
                m_temperature_left.offset(),
                "Temp. left",
                0.0f,
                40.0f,
                ImVec2(width, 80.0f));

            ImGui::PlotLines("Temp. right",
                m_temperature_right.data(),
                m_temperature_right.size(),
                m_temperature_right.offset(),
                "Temp. right",
                0.0f,
                40.0f,
                ImVec2(width, 80.0f));
        });

    pine::gui::render_window("Console",
        []()
        {
            // TODO: Implement functionality.
        });
}

void LocalControlLayer::on_event(pine::Event& e)
{
    m_camera_controller.on_event(e);
}

}; // namespace pineapple

#endif // PINEAPPLE_ENABLE_ZED
