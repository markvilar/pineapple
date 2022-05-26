#include "pineapple/zed/local_control_layer.hpp"

#ifdef PINEAPPLE_ENABLE_ZED

namespace pineapple
{

LocalControlLayer::LocalControlLayer()
    : Layer("LocalControlLayer"), m_CameraController(1.0f),
    m_RecordManager(Pine::FileSystem::GetWorkingDirectory())
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
    framebufferSpecs.Width = m_PanelLayouts["Viewport"].size.x;
    framebufferSpecs.Height = m_PanelLayouts["Viewport"].size.y;
    m_Framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_RendererData2D = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void LocalControlLayer::OnDetach() {}

void LocalControlLayer::OnUpdate(Pine::Timestep ts)
{
    const auto image_request = m_RecordManager.RequestImage(m_ImageSpecs.width, 
        m_ImageSpecs.height, m_ImageSpecs.view);
    if (image_request.has_value())
    {
        const auto& image = image_request.value();
        m_ImageTexture = Pine::Texture2D::Create(ConvertImage(image));
    }

    const auto sensor_data_request = m_RecordManager.RequestSensorData();
    if (sensor_data_request.has_value())
    {
        const auto& data = sensor_data_request.value();

        m_Pressure.push_back(data.pressure);
        m_TemperatureLeft.push_back(data.temperature_left);
        m_TemperatureRight.push_back(data.temperature_right);

        m_AccX.push_back(data.acceleration.x);
        m_AccY.push_back(data.acceleration.y);
        m_AccZ.push_back(data.acceleration.z);

        m_AngX.push_back(data.angular_velocity.x);
        m_AngY.push_back(data.angular_velocity.y);
        m_AngZ.push_back(data.angular_velocity.z);
    }

    const auto specs = m_Framebuffer->GetSpecification();
    const auto viewport = m_PanelLayouts["Viewport"];

    if (viewport.size.x > 0.0f && viewport.size.y > 0.0f
        && (specs.Width != viewport.size.x 
        || specs.Height != viewport.size.y))
    {
        m_Framebuffer->Resize(viewport.size.x, viewport.size.y);
        m_CameraController.OnResize(viewport.size.x, viewport.size.y);
    }

    if (m_ViewportFocused)
        m_CameraController.OnUpdate(ts);

    Pine::RenderCommand::SetClearColor({0.10f, 0.10f, 0.10f, 1.00f});
    Pine::RenderCommand::Clear();

    m_Framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
    Pine::RenderCommand::Clear();
 
    Pine::Renderer2D::BeginScene(m_RendererData2D, 
        m_CameraController.GetCamera());

    if (m_ImageTexture)
    {
        Pine::Renderer2D::DrawQuad(m_RendererData2D,
            {0.0f, 0.0f, 0.0f},
            { (m_ImageSpecs.width / 1000.0f), -(m_ImageSpecs.height / 1000.0f)},
            m_ImageTexture,
            1.0f,
            Pine::Vec4{1.0f, 1.0f, 1.0f, 1.0f});
    }

    Pine::Renderer2D::EndScene(m_RendererData2D);

    m_Framebuffer->Unbind();
}

void LocalControlLayer::OnImGuiRender()
{
    UpdatePanelLayouts();

    Pine::UI::AddMainMenuBar([]() {
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
        m_PanelLayouts["Viewport"].position,
        m_PanelLayouts["Viewport"].size,
        *m_Framebuffer.get(),
        [this]() {
            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();
            Pine::Application::Get().GetImGuiLayer()->BlockEvents(
                !m_ViewportFocused || !m_ViewportHovered);
        });

    Pine::UI::AddWindow("Camera Controls",
        m_PanelLayouts["LeftPanel"].position,
        m_PanelLayouts["LeftPanel"].size,
        [this]() {
            if (ImGui::Button("Start record"))
            {
                m_RecordManager.StartRecord(m_CameraParameters);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
                m_RecordManager.StopRecord();
            }

            ImGui::Separator();

            ImGui::Text("Opened:          %d", m_RecordManager.IsOpened());
            ImGui::Text("Recording:       %d", m_RecordManager.IsRecording());
            ImGui::Text("Stopped:         %d", m_RecordManager.IsStopped());

            ImGui::Text("Space total:     %.2f GB", 
                m_RecordManager.GetTotalSpace() / 1e9);
            ImGui::Text("Space free:      %.2f GB", 
                m_RecordManager.GetFreeSpace() / 1e9);
            ImGui::Text("Space available: %.2f GB", 
                m_RecordManager.GetAvailableSpace() / 1e9);

            ImGui::Separator();
            DrawCameraParameters(m_CameraParameters);
            ImGui::Separator();
            DrawCameraSettings(m_CameraSettings);

            if (ImGui::Button("Request settings"))
            {
                const auto settings_request
                    = m_RecordManager.RequestCameraSettings();
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
                    PINE_INFO(" - Auto w.b.:   {0}", settings.auto_whitebalance);
                    PINE_INFO(" - Enable LED:  {0}", settings.enable_led);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
                m_RecordManager.UpdateCameraSettings(m_CameraSettings);
            }

            ImGui::Separator();
        
            DrawImageSpecification(m_ImageSpecs);
        });

    Pine::UI::AddWindow("Sensor Data",
        m_PanelLayouts["RightPanel"].position,
        m_PanelLayouts["RightPanel"].size,
        [this]() {
            const auto panel_width = m_PanelLayouts["RightPanel"].size.x;
            const auto panel_height = m_PanelLayouts["RightPanel"].size.y;

            ImGui::PlotLines("Acc. X", m_AccX.data(), m_AccX.size(), 
                m_AccX.offset(), "Acceleration X", 
                -10.0f, 10.0f, ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Acc. Y", m_AccY.data(), m_AccY.size(), 
                m_AccY.offset(), "Acceleration Y", 
                -10.0f, 10.0f, ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Acc. Z", m_AccZ.data(), m_AccZ.size(), 
                m_AccZ.offset(), "Acceleration Z", 
                -10.0f, 10.0f, ImVec2(panel_width, 80.0f));

            Pine::UI::AddEmptySpace(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Ang. vel. X", m_AngX.data(), m_AngX.size(), 
                m_AngX.offset(), "Angular velocity X", 
                -30.0f, 30.0f, ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Ang. vel. Y", m_AngY.data(), m_AngY.size(), 
                m_AngY.offset(), "Angular velocity Y", 
                -30.0f, 30.0f, ImVec2(panel_width, 80.0f));
            ImGui::PlotLines("Ang. vel. Z", m_AngZ.data(), m_AngZ.size(), 
                m_AngZ.offset(), "Angular velocity Z", 
                -30.0f, 30.0f, ImVec2(panel_width, 80.0f));

            Pine::UI::AddEmptySpace(0.0f, 10.0f);

            ImGui::Separator();

            ImGui::PlotLines("Pressure", 
                m_Pressure.data(), 
                m_Pressure.size(), 
                m_Pressure.offset(), 
                "Pressure", 
                0.0f, 100000.0f, ImVec2(panel_width, 80.0f));

            ImGui::PlotLines("Temp. left", 
                m_TemperatureLeft.data(), 
                m_TemperatureLeft.size(), 
                m_TemperatureLeft.offset(), 
                "Temp. left", 
                0.0f, 40.0f, ImVec2(panel_width, 80.0f));

            ImGui::PlotLines("Temp. right", 
                m_TemperatureRight.data(), 
                m_TemperatureRight.size(), 
                m_TemperatureRight.offset(), 
                "Temp. right", 
                0.0f, 40.0f, ImVec2(panel_width, 80.0f));
        });

    Pine::UI::AddWindow("Console",
        m_PanelLayouts["BottomPanel"].position,
        m_PanelLayouts["BottomPanel"].size,
        []() {
            // TODO: Implement functionality.
        });
}

void LocalControlLayer::OnEvent(Pine::Event& e)
{
    m_CameraController.OnEvent(e);
}

void LocalControlLayer::UpdatePanelLayouts()
{
    const auto& [window_width, window_height] =
        Pine::Application::Get().GetWindow().GetSize();

    static constexpr auto menu_height = 20.0f;

    const auto& main_menu_layout = m_PanelLayouts["MainMenu"];

    m_PanelLayouts["LeftPanel"] = PanelLayout(
        Pine::Vec2(0.0f * window_width, 0.0f * window_height + menu_height),
        Pine::Vec2(0.2f * window_width, 1.0f * window_height - menu_height));

    m_PanelLayouts["Viewport"] = PanelLayout(
        Pine::Vec2(0.2f * window_width, 0.0f * window_height + menu_height),
        Pine::Vec2(0.6f * window_width, 0.8f * window_height));

    m_PanelLayouts["RightPanel"] = PanelLayout(
        Pine::Vec2(0.8f * window_width, 0.0f * window_height + menu_height),
        Pine::Vec2(0.2f * window_width, 1.0f * window_height - menu_height));

    m_PanelLayouts["BottomPanel"] = PanelLayout(
        Pine::Vec2(0.2f * window_width, 0.8f * window_height + menu_height),
        Pine::Vec2(0.6f * window_width, 0.2f * window_height - menu_height));
}

}; // namespace pineapple

#endif // PINEAPPLE_ENABLE_ZED
