#include "pineapple/zed/remote_control_layer.hpp"

namespace pineapple
{

RemoteControlLayer::RemoteControlLayer()
    : Layer("RemoteControlLayer"), camera_controller(1.0f)
{
}

RemoteControlLayer::~RemoteControlLayer() {}

void RemoteControlLayer::on_attach()
{
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf",
        15.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());

    pine::FramebufferSpecs framebuffer_specs;
    framebuffer_specs.width = 1280;
    framebuffer_specs.height = 720;
    framebuffer = pine::Framebuffer::create(framebuffer_specs);

    quad_data = pine::QuadRenderer::init();

    image_texture = pine::Texture2D::create(m_image);

    pine::gui::set_dark_theme(ImGui::GetStyle());
}

void RemoteControlLayer::on_detach() {}

void RemoteControlLayer::on_update(pine::Timestep ts)
{
    while (!client.message_queue.empty())
    {
        const auto& message = client.message_queue.pop_front();
        on_message(message);
    }

    /* FIXME: Update to pines new camera controller API
    if (viewport_panel.focused)
        camera_controller.OnUpdate(ts);
    */

    pine::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
    pine::RenderCommand::clear();

    framebuffer->bind();
    pine::RenderCommand::set_clear_color({0.1f, 0.1f, 0.1f, 1.0f});
    pine::RenderCommand::clear();

    pine::QuadRenderer::begin_scene(quad_data,
        camera_controller.get_camera());

    if (image_texture)
    {
        auto width = (m_image.get_width() / 1000.0f);
        auto height = -(m_image.get_height() / 1000.0f);
        pine::QuadRenderer::draw_quad(quad_data,
            {0.0f, 0.0f, -0.05f},
            {width, height},
            image_texture,
            1.0f,
            pine::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    pine::QuadRenderer::end_scene(quad_data);
    framebuffer->unbind();

    // Automatically update settings
    if (camera_settings != reference_settings)
    {
        reference_settings = camera_settings;
        send_settings(camera_settings);
    }

    /* TODO: Automatically update stream configuration
    if ()
    {
    }
    */
}

void RemoteControlLayer::on_gui_render()
{
    pine::gui::render_dockspace("dockspace");
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

    viewport_panel = pine::gui::render_viewport("Viewport", *framebuffer.get());
    const auto specs = framebuffer->get_specification();

    if (viewport_panel.size.x > 0.0f && viewport_panel.size.y > 0.0f
        && (specs.width != viewport_panel.size.x
            || specs.height != viewport_panel.size.y))
    {
        framebuffer->resize(viewport_panel.size.x, viewport_panel.size.y);
        camera_controller.on_resize(viewport_panel.size.x,
            viewport_panel.size.y);
    }

    pine::Application::get().get_graphical_interface().block_events(
        !viewport_panel.focused || !viewport_panel.hovered);

    pine::gui::render_window("Camera Controls",
        [this]()
        {
            static char address[256] = "";
            static uint16_t port = 0;

            static constexpr auto control_panel_height = 200;
            const auto content_size = ImGui::GetContentRegionAvail();

            ImGui::InputText("Server Address", address, IM_ARRAYSIZE(address));
            ImGui::InputInt("Server Port", (int*)&port, 0, 0);
            ImGui::Text("Client connected: %d", is_connected(client));

            if (ImGui::Button("Connect", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::connect(client, std::string(address), port);
            }
            ImGui::SameLine();
            if (ImGui::Button("Disconnect",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                pine::disconnect(client);
            }

            ImGui::Separator();

            // ----------------------------------------------------------------
            // Camera controls
            // ----------------------------------------------------------------

            if (ImGui::Button("Record", ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::ControlMessage message;
                message.topic = "/desktop/control_request";

                message.command = "start_record";
                message.resolution = camera_parameters.resolution;
                message.compression = camera_parameters.compression;
                message.fps = camera_parameters.fps;
                message.timeout = camera_parameters.timeout;
                message.require_sensors = camera_parameters.require_sensors;
                message.enable_depth = camera_parameters.enable_depth;

                message.enable_image_enhancement =
                    camera_parameters.enable_image_enhancement;
                message.disable_self_calibration =
                    camera_parameters.disable_self_calibration;

                send_message(message);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop record",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::ControlMessage message;
                message.topic = "/desktop/control_request";

                message.command = "stop_record";
                message.resolution = camera_parameters.resolution;
                message.compression = camera_parameters.compression;
                message.fps = camera_parameters.fps;
                message.timeout = camera_parameters.timeout;
                message.require_sensors = camera_parameters.require_sensors;
                message.enable_depth = camera_parameters.enable_depth;

                message.enable_image_enhancement =
                    camera_parameters.enable_image_enhancement;
                message.disable_self_calibration =
                    camera_parameters.disable_self_calibration;

                send_message(message);
            }

            if (ImGui::Button("Start stream",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::StreamMessage message;
                message.topic = "/desktop/stream_request";

                message.command = "start_stream";
                message.width = stream_config.width;
                message.height = stream_config.height;
                message.period = stream_config.period;

                send_message(message);
            }

            ImGui::SameLine();

            if (ImGui::Button("Stop stream",
                    ImVec2(0.50f * content_size.x, 30.0f)))
            {
                zed::StreamMessage message;
                message.topic = "/desktop/stream_request";

                message.command = "stop_stream";
                message.width = stream_config.width;
                message.height = stream_config.height;
                message.period = stream_config.period;

                send_message(message);
            }

            ImGui::Separator();

            draw_camera_parameters(camera_parameters);

            ImGui::Separator();

            draw_camera_settings(camera_settings);

            ImGui::Separator();

            ImGui::InputScalar("Image width",
                ImGuiDataType_U16,
                &stream_config.width,
                NULL,
                NULL);
            ImGui::InputScalar("Image height",
                ImGuiDataType_U16,
                &stream_config.height,
                NULL,
                NULL);

            pine::gui::slider_scalar<float>("Stream period",
                &stream_config.period,
                0.05f,
                5.00f);
        });
}

void RemoteControlLayer::on_event(pine::Event& e)
{
    camera_controller.on_event(e);
}

void RemoteControlLayer::send_settings(
    const zed::CameraSettings& settings) const
{
    zed::SettingsMessage message;
    message.topic = "/desktop/settings_request";

    message.brightness = settings.brightness;
    message.contrast = settings.contrast;
    message.hue = settings.hue;
    message.saturation = settings.saturation;
    message.sharpness = settings.sharpness;
    message.gamma = settings.gamma;
    message.gain = settings.gain;
    message.exposure = settings.exposure;
    message.whitebalance = settings.whitebalance;
    message.auto_exposure = settings.auto_exposure;
    message.auto_whitebalance = settings.auto_whitebalance;

    send_message(message);
}

/*
void RemoteControlLayer::send_stream_config()
{
}
*/

void RemoteControlLayer::on_message(const std::vector<uint8_t>& buffer)
{
    msgpack::object_handle handle =
        msgpack::unpack((char*)buffer.data(), buffer.size());
    msgpack::object object = handle.get();

    try
    {
        auto message = object.as<zed::ControlMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::SettingsMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::SensorMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };

    try
    {
        auto message = object.as<zed::ImageMessage>();
        on_message(message);
        return;
    }
    catch (const msgpack::v1::type_error& error)
    {
    };
}

void RemoteControlLayer::on_message(const zed::ControlMessage& message)
{
    PINE_INFO("Got control message.");
    if (message.topic == "/camera/control_reponse")
    {
        remote_parameters.resolution = message.resolution;
        remote_parameters.compression = message.compression;
        remote_parameters.fps = message.fps;
        remote_parameters.timeout = message.timeout;
        remote_parameters.enable_image_enhancement 
            = message.enable_image_enhancement;
        remote_parameters.disable_self_calibration 
            = message.disable_self_calibration;
        remote_parameters.require_sensors = message.require_sensors;
        remote_parameters.enable_depth = message.enable_depth;
    }
}

void RemoteControlLayer::on_message(const zed::SettingsMessage& message)
{
    PINE_INFO("Got settings message.");
    if (message.topic == "/camera/settings_response")
    {
        remote_settings.brightness = message.brightness;
        remote_settings.contrast = message.contrast;
        remote_settings.hue = message.hue;
        remote_settings.saturation = message.saturation;
        remote_settings.sharpness = message.sharpness;
        remote_settings.gamma = message.gamma;
        remote_settings.gain = message.gain;
        remote_settings.exposure = message.exposure;
        remote_settings.whitebalance = message.whitebalance;
        remote_settings.auto_exposure = message.auto_exposure;
        remote_settings.auto_whitebalance = message.auto_whitebalance;
    }
}

void RemoteControlLayer::on_message(const zed::SensorMessage& message) {}

void RemoteControlLayer::on_message(const zed::ImageMessage& message)
{
    if (message.topic == "/camera/image")
    {
        m_image = pine::Image(message.data.data(),
            message.width,
            message.height,
            pine::ImageFormat::BGRA);
        image_texture = pine::Texture2D::create(m_image);
    }
}

}; // namespace pineapple
