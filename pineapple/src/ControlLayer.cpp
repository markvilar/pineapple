#include "Pineapple/ControlLayer.hpp"

namespace Pineapple
{

ControlLayer::ControlLayer()
    : Layer("ControlLayer"), m_CameraController(1280.0f / 720.0f, false)
{
}

ControlLayer::~ControlLayer() {}

void ControlLayer::OnAttach()
{
    m_Client = std::make_shared<Client>();

    Pine::Framebuffer::Specification fbSpec;
    fbSpec.Width = 1280;
    fbSpec.Height = 720;
    m_Framebuffer = Pine::Framebuffer::Create(fbSpec);

    Pine::Renderer2D::Init();
    Pine::UI::SetDarkTheme(ImGui::GetStyle());
}

void ControlLayer::OnDetach() {}

void ControlLayer::OnUpdate(Pine::Timestep ts)
{
    while (!m_Client->Incoming().empty())
    {
        auto message = m_Client->Incoming().pop_front().Msg;
        OnMessage(message);
    }

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

    Pine::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Pine::Renderer2D::EndScene();
    m_Framebuffer->Unbind();
}

void ControlLayer::OnImGuiRender()
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
        m_Framebuffer,
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

            AddCombo("Flip mode", flipModes, []() {});
            AddCombo("Resolution", resolutions, []() {});
            AddCombo("Compression", compressionModes, []() {});

            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            SliderScalar("Target FPS", &m_CameraParameters.CameraFPS, 0, 100);
            SliderScalar("Timeout", &m_CameraParameters.OpenTimeout,
                -1.0f,
                10.0f);

            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            ImGui::Checkbox("Image enhancement",
                &m_CameraParameters.EnableImageEnhancement);
            ImGui::Checkbox("Disable self calib.",
                &m_CameraParameters.DisableSelfCalibration);
            ImGui::Checkbox("Require sensors",
                &m_CameraParameters.RequireSensors);
            ImGui::Checkbox("Enable depth", &m_CameraParameters.EnableDepth);

            ImGui::Separator();

            SliderScalar("Brightness", 
                &m_CameraSettings.Brightness, 0, 8);
            SliderScalar("Contrast", 
                &m_CameraSettings.Contrast, 0, 8);
            SliderScalar("Hue", 
                &m_CameraSettings.Hue, 0, 11);
            SliderScalar("Saturation", 
                &m_CameraSettings.Saturation, 0, 8);
            SliderScalar("Sharpness", 
                &m_CameraSettings.Sharpness, 0, 8);
            SliderScalar("Gain", 
                &m_CameraSettings.Gain, 0, 100);
            SliderScalar("Exposure", 
                &m_CameraSettings.Exposure, 0, 100);
            SliderScalar("Whitebalance temp.",
                &m_CameraSettings.Whitebalance,
                2800,
                6500);

            ImGui::Dummy(ImVec2(0.0f, 20.0f));

            ImGui::Checkbox("Auto exposure", 
                &m_CameraSettings.AutoExposure);
            ImGui::Checkbox("Auto whitebalance",
                &m_CameraSettings.AutoWhitebalance);
            ImGui::Checkbox("Enable LED ", 
                &m_CameraSettings.EnableLED);
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

void ControlLayer::OnEvent(Pine::Event& e) { m_CameraController.OnEvent(e); }

void ControlLayer::OnMessage(Pine::TCP::Message<MessageTypes>& message)
{
    /*
    switch (message.Header.ID)
    {
    // Server messages.
    case MessageTypes::ServerPing:
        m_ClientPanel.OnServerPing(message);
        break;
    case MessageTypes::ServerAccept:
        m_ClientPanel.OnServerAccept(message);
        break;
    case MessageTypes::ServerDeny:
        m_ClientPanel.OnServerDeny(message);
        break;

    // Sensor control messages.
    case MessageTypes::SensorControllerAccept:
        m_SensorControllerPanel.OnSensorControllerAccept(message);
        break;
    case MessageTypes::SensorControllerDeny:
        m_SensorControllerPanel.OnSensorControllerDeny(message);
        break;

    // Image and image stream messages.
    case MessageTypes::Image:
        m_SensorControllerPanel.OnImage(message);
        break;
    case MessageTypes::ImageDeny:
        m_SensorControllerPanel.OnImageDeny(message);
        break;
    case MessageTypes::ImageStream:
        m_SensorControllerPanel.OnImageStream(message);
        break;
    case MessageTypes::ImageStreamDeny:
        m_SensorControllerPanel.OnImageStreamDeny(message);
        break;

    // TODO: Implement.
    // Initialization parameter update messages.
    case MessageTypes::InitParametersAccept:
        break;
    case MessageTypes::InitParametersDeny:
        break;

    // TODO: Implement.
    // Recording parameter update messages.
    case MessageTypes::RecordingParametersAccept:
        break;
    case MessageTypes::RecordingParametersDeny:
        break;

    // TODO: Implement.
    // Runtime parameter update messages.
    case MessageTypes::RuntimeParametersAccept:
        break;
    case MessageTypes::RuntimeParametersDeny:
        break;

    // TODO: Implement.
    // Video setting messages.
    case MessageTypes::VideoSettingsRequest:
        break;
    case MessageTypes::VideoSettings:
        break;
    }
    */
}

} // namespace Pineapple
