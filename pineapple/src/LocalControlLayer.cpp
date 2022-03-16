#include "Pineapple/LocalControlLayer.hpp"

namespace Pineapple
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
    framebufferSpecs.Width = m_PanelLayouts["Viewport"].Size.x;
    framebufferSpecs.Height = m_PanelLayouts["Viewport"].Size.y;
    m_Framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_RendererData2D = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void LocalControlLayer::OnDetach() {}

void LocalControlLayer::OnUpdate(Pine::Timestep ts)
{
    const auto imageRequest = m_RecordManager.RequestImage(
        m_ImageConfig.Width, 
        m_ImageConfig.Height, 
        m_ImageConfig.Type);

    if (imageRequest.has_value())
    {
        m_ImageTexture = Pine::Texture2D::Create(imageRequest.value());
    }

    const auto specs = m_Framebuffer->GetSpecification();
    const auto viewport = m_PanelLayouts["Viewport"];

    if (viewport.Size.x > 0.0f && viewport.Size.y > 0.0f
        && (specs.Width != viewport.Size.x 
        || specs.Height != viewport.Size.y))
    {
        m_Framebuffer->Resize(viewport.Size.x, viewport.Size.y);
        m_CameraController.OnResize(viewport.Size.x, viewport.Size.y);
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
            { (m_ImageConfig.Width / 1000.0f), -(m_ImageConfig.Height / 1000.0f)},
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
        static bool showImGuiDemoWindow = false;
        static bool showImGuiMetrics = false;
        static bool showImGuiStackTool = false;

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
            ImGui::Checkbox("Show ImGui demo window", &showImGuiDemoWindow);
            ImGui::Checkbox("Show ImGui metrics", &showImGuiMetrics);
            ImGui::Checkbox("Show ImGui stack tool", &showImGuiStackTool);
            ImGui::EndMenu();
        }

        if (showImGuiDemoWindow)
            ImGui::ShowDemoWindow();
        if (showImGuiMetrics)
            ImGui::ShowMetricsWindow();
        if (showImGuiStackTool)
            ImGui::ShowStackToolWindow();
    });

    Pine::UI::AddViewport("Viewport",
        m_PanelLayouts["Viewport"].Position,
        m_PanelLayouts["Viewport"].Size,
        *m_Framebuffer.get(),
        [this]() {
            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();
            Pine::Application::Get().GetImGuiLayer()->BlockEvents(
                !m_ViewportFocused || !m_ViewportHovered);
        });

    Pine::UI::AddWindow("Camera Controls",
        m_PanelLayouts["LeftPanel"].Position,
        m_PanelLayouts["LeftPanel"].Size,
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
            DrawCameraParameters(m_CameraParameters);
            ImGui::Separator();
            DrawCameraSettings(m_CameraSettings);

            if (ImGui::Button("Request settings"))
            {
                const auto settingsRequest
                    = m_RecordManager.RequestCameraSettings();
                if (settingsRequest.has_value())
                {
                    const auto settings = settingsRequest.value();
                    PINE_INFO("Camera settings:");
                    PINE_INFO(" - Brightness:  {0}", settings.Brightness);
                    PINE_INFO(" - Contrast:    {0}", settings.Contrast);
                    PINE_INFO(" - Hue:         {0}", settings.Hue);
                    PINE_INFO(" - Saturation:  {0}", settings.Saturation);
                    PINE_INFO(" - Sharpness:   {0}", settings.Sharpness);
                    PINE_INFO(" - Gain:        {0}", settings.Gain);
                    PINE_INFO(" - Exposure:    {0}", settings.Exposure);
                    PINE_INFO(" - Whiteb.:     {0}", settings.Whitebalance);
                    PINE_INFO(" - Auto expos.: {0}", settings.AutoExposure);
                    PINE_INFO(" - Auto w.b.:   {0}", settings.AutoWhitebalance);
                    PINE_INFO(" - Enable LED:  {0}", settings.EnableLED);
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
                m_RecordManager.UpdateCameraSettings(m_CameraSettings);
            }

            ImGui::Separator();
        
            DrawImageConfiguration(m_ImageConfig);
        });

    Pine::UI::AddWindow("Sensor Data",
        m_PanelLayouts["RightPanel"].Position,
        m_PanelLayouts["RightPanel"].Size,
        []() {
            // TODO: Implement functionality.
            // TODO: Plotting of accelerometer.
            // TODO: Plotting of gyroscope.
        });

    Pine::UI::AddWindow("Console",
        m_PanelLayouts["BottomPanel"].Position,
        m_PanelLayouts["BottomPanel"].Size,
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
    const auto& [windowWidth, windowHeight] =
        Pine::Application::Get().GetWindow().GetSize();

    static constexpr auto menuHeight = 20.0f;

    const auto& mainMenuLayout = m_PanelLayouts["MainMenu"];

    m_PanelLayouts["LeftPanel"] = PanelLayout(
        Pine::Vec2(0.0f * windowWidth, 0.0f * windowHeight + menuHeight),
        Pine::Vec2(0.2f * windowWidth, 1.0f * windowHeight - menuHeight));

    m_PanelLayouts["Viewport"] = PanelLayout(
        Pine::Vec2(0.2f * windowWidth, 0.0f * windowHeight + menuHeight),
        Pine::Vec2(0.6f * windowWidth, 0.8f * windowHeight));

    m_PanelLayouts["RightPanel"] = PanelLayout(
        Pine::Vec2(0.8f * windowWidth, 0.0f * windowHeight + menuHeight),
        Pine::Vec2(0.2f * windowWidth, 1.0f * windowHeight - menuHeight));

    m_PanelLayouts["BottomPanel"] = PanelLayout(
        Pine::Vec2(0.2f * windowWidth, 0.8f * windowHeight + menuHeight),
        Pine::Vec2(0.6f * windowWidth, 0.2f * windowHeight - menuHeight));
}

} // namespace Pineapple
