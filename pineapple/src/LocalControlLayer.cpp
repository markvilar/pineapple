#include "Pineapple/LocalControlLayer.hpp"

namespace Pineapple
{

LocalControlLayer::LocalControlLayer()
    : Layer("LocalControlLayer"), m_CameraController(1.0f),
    m_CameraInterface(Pine::FileSystem::GetWorkingDirectory())
{
}

LocalControlLayer::~LocalControlLayer() {}

void LocalControlLayer::OnAttach()
{
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    Pine::Framebuffer::Specification framebufferSpecs;
    framebufferSpecs.Width = 1280;
    framebufferSpecs.Height = 720;
    m_Framebuffer = Pine::Framebuffer::Create(framebufferSpecs);

    m_RendererData2D = Pine::Renderer2D::Init();

    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void LocalControlLayer::OnDetach() {}

void LocalControlLayer::OnUpdate(Pine::Timestep ts)
{
    auto spec = m_Framebuffer->GetSpecification();
    if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f
        && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
    {
        m_Framebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x),
            static_cast<uint32_t>(m_ViewportSize.y));
        m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
    }

    if (m_ViewportFocused)
        m_CameraController.OnUpdate(ts);

    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    m_Framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.2f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();
 
    Pine::Renderer2D::BeginScene(m_RendererData2D, 
        m_CameraController.GetCamera());

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
        []() {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Camera Controls",
        m_PanelLayouts["LeftPanel"].Position,
        m_PanelLayouts["LeftPanel"].Size,
        [this]() {
            if (ImGui::Button("Start record"))
            {
                m_CameraInterface.StartRecord(m_CameraParameters);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
                m_CameraInterface.StopRecord();
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
            }

            ImGui::Separator();
            DrawCameraParameters(m_CameraParameters);
            ImGui::Separator();
            DrawCameraSettings(m_CameraSettings);
        });

    Pine::UI::AddWindow("Sensor Data",
        m_PanelLayouts["RightPanel"].Position,
        m_PanelLayouts["RightPanel"].Size,
        []() {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Bottom",
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
