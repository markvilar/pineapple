#include "Pineapple/RemoteControlLayer.hpp"

namespace Pineapple
{

RemoteControlLayer::RemoteControlLayer()
    : Layer("RemoteControlLayer"), m_CameraController(1.0f)
{
}

RemoteControlLayer::~RemoteControlLayer() {}

void RemoteControlLayer::OnAttach()
{
    UpdatePanelLayouts();

    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    Pine::Framebuffer::Specification framebufferSpecs;
    framebufferSpecs.Width = 1280;
    framebufferSpecs.Height = 720;
    m_Framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_RendererData = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void RemoteControlLayer::OnDetach() {}

void RemoteControlLayer::OnUpdate(Pine::Timestep ts)
{
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

    // Clear background color.
    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    m_Framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.2f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    Pine::Renderer2D::BeginScene(m_RendererData, m_CameraController.GetCamera());

    Pine::Renderer2D::EndScene(m_RendererData);
    m_Framebuffer->Unbind();
}

void RemoteControlLayer::OnImGuiRender()
{
    constexpr auto menuBarHeight = 20;
    const auto windowSize = Pine::Application::Get().GetWindow().GetSize();

    const std::pair<uint32_t, uint32_t> uiPosition = {0, menuBarHeight};
    const std::pair<uint32_t, uint32_t> uiSize = {windowSize.first,
        windowSize.second - menuBarHeight};

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

    Pine::UI::AddWindow("Left",
        m_PanelLayouts["LeftPanel"].Position,
        m_PanelLayouts["LeftPanel"].Size,
        [this]() {
            if (ImGui::Button("Start record"))
            {
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
            }

            ImGui::Separator();
            DrawCameraParameters(m_CameraParameters);
            ImGui::Separator();
            DrawCameraSettings(m_CameraSettings);
            ImGui::Separator();
            DrawImageConfiguration(m_ImageConfig);
        });

    Pine::UI::AddWindow("Right",
        m_PanelLayouts["BottomPanel"].Position,
        m_PanelLayouts["BottomPanel"].Size,
        []() {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Bottom",
        Pine::Vec2(uiPosition.first + 0.20 * uiSize.first,
            uiPosition.second + 0.70 * uiSize.second),
        Pine::Vec2(0.60 * uiSize.first, 0.30 * uiSize.second),
        []() {
            // TODO: Implement functionality.
        });
}

void RemoteControlLayer::OnEvent(Pine::Event& e)
{
    m_CameraController.OnEvent(e);
}

void RemoteControlLayer::OnMessage(const Pine::Message& message)
{
}

void RemoteControlLayer::UpdatePanelLayouts()
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

}; // namespace Pineapple
