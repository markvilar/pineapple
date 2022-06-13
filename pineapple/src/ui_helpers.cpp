#include "pineapple/ui_helpers.hpp"

namespace pineapple
{

void draw_camera_parameters(zed::CameraParameters& parameters)
{
    static const std::array<std::pair<std::string, zed::Resolution>, 4>
        resolution_options = {{{"HD2K", zed::Resolution::HD2K},
            {"HD1080", zed::Resolution::HD1080},
            {"HD720", zed::Resolution::HD720},
            {"VGA", zed::Resolution::VGA}}};

    static const std::array<std::pair<std::string, zed::Compression>, 5>
        compression_options = {{{"Lossless", zed::Compression::LOSSLESS},
            {"H264", zed::Compression::H264},
            {"H265", zed::Compression::H265},
            {"H264, lossless", zed::Compression::H264_LOSSLESS},
            {"H265, lossless", zed::Compression::H265_LOSSLESS}}};

    Pine::UI::AddCombo("Resolution",
        &parameters.resolution,
        resolution_options);
    Pine::UI::AddCombo("Compression",
        &parameters.compression,
        compression_options);

    Pine::UI::SliderScalar("Target FPS", &parameters.fps, 0, 100);
    Pine::UI::SliderScalar("Timeout", &parameters.timeout, -1.0f, 10.0f);

    ImGui::Checkbox("Image enhancement", &parameters.enable_image_enhancement);
    ImGui::Checkbox("Disable self calib.",
        &parameters.disable_self_calibration);
    ImGui::Checkbox("Require sensors", &parameters.require_sensors);
    ImGui::Checkbox("Enable depth", &parameters.enable_depth);
}

void draw_camera_settings(zed::CameraSettings& settings)
{
    Pine::UI::SliderScalar("Brightness", &settings.brightness, 0, 8);
    Pine::UI::SliderScalar("Contrast", &settings.contrast, 0, 8);
    Pine::UI::SliderScalar("Hue", &settings.hue, 0, 11);
    Pine::UI::SliderScalar("Saturation", &settings.saturation, 0, 8);
    Pine::UI::SliderScalar("Sharpness", &settings.sharpness, 0, 8);
    Pine::UI::SliderScalar("Gamma", &settings.gamma, 1, 9);
    Pine::UI::SliderScalar("Gain", &settings.gain, 0, 100);
    Pine::UI::SliderScalar("Exposure", &settings.exposure, 0, 100);
    Pine::UI::SliderScalar("Whitebalance temp.",
        &settings.whitebalance,
        2800,
        6500);

    ImGui::Checkbox("Auto exposure", &settings.auto_exposure);
    ImGui::Checkbox("Auto whitebalance", &settings.auto_whitebalance);
    ImGui::Checkbox("Enable LED", &settings.enable_led);
}

void draw_image_specification(zed::ImageSpecification& specifications)
{
    static const std::array<std::pair<std::string, zed::View>, 5> view_options =
        {{{"Left", zed::View::LEFT},
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
    Pine::UI::AddCombo("View", &specifications.view, view_options);
}

}; // namespace pineapple
