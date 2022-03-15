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
    //m_Client = std::make_shared<Client>();

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
    auto spec = m_Framebuffer->GetSpecification();
    if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f
        && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
    {
        m_Framebuffer->Resize((uint32_t)m_ViewportSize.x,
            (uint32_t)m_ViewportSize.y);
        m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
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
        Pine::Vec2(uiPosition.first + 0.20 * uiSize.first,
            uiPosition.second + 0.00 * uiSize.second),
        Pine::Vec2(0.60 * uiSize.first, 0.70 * uiSize.second),
        *m_Framebuffer.get(),
        []() {
            // TODO: Implement functionality.
        });

    Pine::UI::AddWindow("Left",
        Pine::Vec2(uiPosition.first + 0.00 * uiSize.first,
            uiPosition.second + 0.00 * uiSize.second),
        Pine::Vec2(0.20 * uiSize.first, 1.00 * uiSize.second),
        [this]() {
            static auto brightness = 0;
            static auto contrast = 0;
            static auto hue = 0;
            static auto saturation = 0;
            static auto sharpness = 0;
            static auto gain = 0;
            static auto exposure = 0;
            static auto whitebalanceTemp = 0;

            static auto aecagc = false;
            static auto whitebalanceAuto = false;
            static auto ledStatus = false;

            if (ImGui::Button("Start record"))
            {
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record"))
            {
            }

            if (ImGui::Button("Update parameters"))
            {
            }

            ImGui::SameLine();

            if (ImGui::Button("Update settings"))
            {
            }

            ImGui::Separator();

            const std::array<std::pair<std::string, ZED::FlipMode>, 3>
                flipModes = {std::make_pair("Off", ZED::FlipMode::OFF),
                    std::make_pair("On", ZED::FlipMode::ON),
                    std::make_pair("Auto", ZED::FlipMode::AUTO)};

            const std::array<std::pair<std::string, ZED::Resolution>, 4>
                resolutions = {std::make_pair("HD2K", ZED::Resolution::HD2K),
                    std::make_pair("HD1080", ZED::Resolution::HD1080),
                    std::make_pair("HD720", ZED::Resolution::HD720),
                    std::make_pair("VGA", ZED::Resolution::VGA)};

            const std::array<std::pair<std::string, ZED::CompressionMode>, 3>
                compressionModes = {
                    std::make_pair("Lossless", ZED::CompressionMode::LOSSLESS),
                    std::make_pair("H264", ZED::CompressionMode::H264),
                    std::make_pair("H265", ZED::CompressionMode::H265)};

            Pine::UI::AddCombo("Flip mode",
                &m_CameraParameters.CameraFlip,
                flipModes);
            Pine::UI::AddCombo("Resolution",
                &m_CameraParameters.CameraResolution,
                resolutions);
            Pine::UI::AddCombo("Compression",
                &m_CameraParameters.Compression,
                compressionModes);

            Pine::UI::AddEmptySpace(0.0f, 20.0f);

            Pine::UI::SliderScalar("Target FPS",
                &m_CameraParameters.CameraFPS,
                0,
                100);
            Pine::UI::SliderScalar("Timeout",
                &m_CameraParameters.OpenTimeout,
                -1.0f,
                10.0f);

            Pine::UI::AddEmptySpace(0.0f, 20.0f);

            ImGui::Checkbox("Image enhancement",
                &m_CameraParameters.EnableImageEnhancement);
            ImGui::Checkbox("Disable self calib.",
                &m_CameraParameters.DisableSelfCalibration);
            ImGui::Checkbox("Require sensors",
                &m_CameraParameters.RequireSensors);
            ImGui::Checkbox("Enable depth", &m_CameraParameters.EnableDepth);

            ImGui::Separator();

            Pine::UI::SliderScalar("Brightness",
                &m_CameraSettings.Brightness,
                0,
                8);
            Pine::UI::SliderScalar("Contrast",
                &m_CameraSettings.Contrast,
                0,
                8);
            Pine::UI::SliderScalar("Hue", &m_CameraSettings.Hue, 0, 11);
            Pine::UI::SliderScalar("Saturation",
                &m_CameraSettings.Saturation,
                0,
                8);
            Pine::UI::SliderScalar("Sharpness",
                &m_CameraSettings.Sharpness,
                0,
                8);
            Pine::UI::SliderScalar("Gain", &m_CameraSettings.Gain, 0, 100);
            Pine::UI::SliderScalar("Exposure",
                &m_CameraSettings.Exposure,
                0,
                100);
            Pine::UI::SliderScalar("Whitebalance temp.",
                &m_CameraSettings.Whitebalance,
                2800,
                6500);

            Pine::UI::AddEmptySpace(0.0f, 20.0f);

            ImGui::Checkbox("Auto exposure", &m_CameraSettings.AutoExposure);
            ImGui::Checkbox("Auto whitebalance",
                &m_CameraSettings.AutoWhitebalance);
            ImGui::Checkbox("Enable LED ", &m_CameraSettings.EnableLED);
        });

    Pine::UI::AddWindow("Right",
        Pine::Vec2(uiPosition.first + 0.80 * uiSize.first,
            uiPosition.second + 0.00 * uiSize.second),
        Pine::Vec2(0.60 * uiSize.first, 1.00 * uiSize.second),
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

}; // namespace Pineapple
