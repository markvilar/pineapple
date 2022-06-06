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
    UpdatePanelLayouts();

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

    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    m_framebuffer->Bind();
    Pine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Pine::RenderCommand::Clear();

    Pine::Renderer2D::BeginScene(m_renderer_data,
        m_camera_controller.GetCamera());

    Pine::Renderer2D::EndScene(m_renderer_data);
    m_framebuffer->Unbind();
}

void RemoteControlLayer::OnImGuiRender()
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
            static char address[256] = "";
            static uint16_t port = 0;
            ImGui::InputText("Address", address, IM_ARRAYSIZE(address));
            ImGui::InputInt("Port", (int*)&port);
            ImGui::Text("Client connected: %d", IsConnected(m_client));

            if (ImGui::Button("Connect"))
            {
                Pine::Connect(m_client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect"))
            {
                Pine::Disconnect(m_client);
            }

            ImGui::Separator();

            // ----------------------------------------------------------------
            // Camera controls
            // ----------------------------------------------------------------

            static constexpr auto control_panel_height = 200;
            const auto content_size = ImGui::GetContentRegionAvail();

            ImGui::PushItemWidth(0.33f * content_size.x);

            if (ImGui::Button("Record", ImVec2(0.50f * content_size.x, 0.0f)))
            {
                if (Pine::IsConnected(m_client))
                {
                    zed::ControlService::Request request;
                    request.body.action = zed::CameraAction::START_RECORD;

                    MemoryOutputArchive output_archive;
                    output_archive.serialize(request);

                    const auto& buffer = output_archive.get_buffer();
                    Pine::Send(m_client, buffer.data(), buffer.size());
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop record",
                    ImVec2(0.50f * content_size.x, 0.0f)))
            {
                zed::ControlService::Request request;
                request.body.action = zed::CameraAction::STOP_RECORD;

                MemoryOutputArchive output_archive;
                output_archive.serialize(request);

                const auto& buffer = output_archive.get_buffer();
                Pine::Send(m_client, buffer.data(), buffer.size());
            }

            ImGui::PopItemWidth();

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

void RemoteControlLayer::UpdatePanelLayouts()
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
