#include "pineapple/zed/remote_control_layer.hpp"

namespace pineapple
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
    while (!m_Client.MessageQueue.empty())
    {
        OnMessage(m_Client.MessageQueue.pop_front());
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

    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    m_Framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    Pine::Renderer2D::BeginScene(m_RendererData, m_CameraController.GetCamera());

    Pine::Renderer2D::EndScene(m_RendererData);
    m_Framebuffer->Unbind();
}

void RemoteControlLayer::OnImGuiRender()
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
            
            static char address[256] = "";
            static uint16_t port = 0;
            ImGui::InputText("Address", address, IM_ARRAYSIZE(address));
            ImGui::InputInt("Port", (int*)&port);
            ImGui::Text("Client connected: %d", IsConnected(m_Client));

            if (ImGui::Button("Connect"))
            {
                Pine::Connect(m_Client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect"))
            {
                Pine::Disconnect(m_Client);
            }

            ImGui::Separator();

            if (ImGui::Button("Start record"))
            {
                // TODO: Format message
                // TODO: Send message
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
                // TODO: Format message
                // TODO: Send message
            }

            ImGui::Separator();
            DrawCameraParameters(m_CameraParameters);
            ImGui::Separator();
            DrawCameraSettings(m_CameraSettings);
            ImGui::Separator();
            DrawImageSpecification(m_ImageSpecs);
        });

    Pine::UI::AddWindow("Sensor Data",
        m_PanelLayouts["RightPanel"].position,
        m_PanelLayouts["RightPanel"].size,
        []() {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Console",
        m_PanelLayouts["BottomPanel"].position,
        m_PanelLayouts["BottomPanel"].size,
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
    PINE_INFO("Got message.");
}

void RemoteControlLayer::UpdatePanelLayouts()
{
    const auto& [window_width, window_height] =
        Pine::Application::Get().GetWindow().GetSize();

    static constexpr auto menu_height = 20.0f;

    const auto& mainMenuLayout = m_PanelLayouts["MainMenu"];

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
