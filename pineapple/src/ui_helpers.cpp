#include "pineapple/ui_helpers.hpp"

namespace pineapple
{

void draw_camera_parameters(zed::CameraParameters& parameters)
{
    /*
    static const std::array<std::pair<const char*, zed::Resolution>, 4>
        resolution_options = {{
            {"HD2K", zed::Resolution::HD2K},
            {"HD1080", zed::Resolution::HD1080},
            {"HD720", zed::Resolution::HD720},
            {"VGA", zed::Resolution::VGA}}};

    static const std::array<std::pair<const char*, zed::Compression>, 5>
        compression_options = {{
            {"Lossless", zed::Compression::LOSSLESS},
            {"H264", zed::Compression::H264},
            {"H265", zed::Compression::H265},
            {"H264, lossless", zed::Compression::H264_LOSSLESS},
            {"H265, lossless", zed::Compression::H265_LOSSLESS}}};

    pine::gui::dropdown("Resolution",
        &parameters.resolution,
        resolution_options);
    pine::gui::dropdown("Compression",
        &parameters.compression,
        compression_options);

    pine::gui::slider_scalar<uint8_t>("Target FPS", &parameters.fps, 0, 100);
    pine::gui::slider_scalar<float>("Timeout", &parameters.timeout, -1.0f, 10.0f);

    ImGui::Checkbox("Image enhancement", &parameters.enable_image_enhancement);
    ImGui::Checkbox("Disable self calib.",
        &parameters.disable_self_calibration);
    ImGui::Checkbox("Require sensors", &parameters.require_sensors);
    ImGui::Checkbox("Enable depth", &parameters.enable_depth);
    */
}

void draw_camera_settings(zed::CameraSettings& settings)
{
    pine::gui::slider_scalar<int>("Brightness", &settings.brightness, 0, 8);
    pine::gui::slider_scalar<int>("Contrast", &settings.contrast, 0, 8);
    pine::gui::slider_scalar<int>("Hue", &settings.hue, 0, 11);
    pine::gui::slider_scalar<int>("Saturation", &settings.saturation, 0, 8);
    pine::gui::slider_scalar<int>("Sharpness", &settings.sharpness, 0, 8);
    pine::gui::slider_scalar<int>("Gamma", &settings.gamma, 1, 9);
    pine::gui::slider_scalar<int>("Gain", &settings.gain, 0, 100);
    pine::gui::slider_scalar<int>("Exposure", &settings.exposure, 0, 100);
    pine::gui::slider_scalar<int>("Whitebalance temp.",
        &settings.whitebalance,
        2800,
        6500);

    ImGui::Checkbox("Auto exposure", &settings.auto_exposure);
    ImGui::Checkbox("Auto whitebalance", &settings.auto_whitebalance);
    ImGui::Checkbox("Enable LED", &settings.enable_led);
}

void draw_image_specification(zed::ImageSpecification& specifications)
{
    /*
    static const std::array<std::pair<const char*, zed::View>, 5> view_options =
        {{
            {"Left", zed::View::LEFT},
            {"Right", zed::View::RIGHT},
            {"Left, gray", zed::View::LEFT_GRAY},
            {"Right, gray", zed::View::RIGHT_GRAY},
            {"Side by side", zed::View::SIDE_BY_SIDE}}};

    ImGui::InputScalar("Image width",
        ImGuiDataType_U32,
        &specifications.width,
        NULL,
        NULL);
    ImGui::InputScalar("Image height",
        ImGuiDataType_U32,
        &specifications.height,
        NULL,
        NULL);
    pine::gui::dropdown("View", &specifications.view, view_options);
    */
}

}; // namespace pineapple
