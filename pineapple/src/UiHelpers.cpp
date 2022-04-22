#include "Pineapple/UiHelpers.hpp"

namespace Pineapple 
{

void DrawCameraParameters(Zed::CameraParameters& parameters)
{
    static const std::array<std::pair<std::string, Zed::Resolution>, 4>
        resolution_options = 
        {{
            {"HD2K", Zed::Resolution::HD2K},
            {"HD1080", Zed::Resolution::HD1080},
            {"HD720", Zed::Resolution::HD720},
            {"VGA", Zed::Resolution::VGA}
        }};

    static const std::array<std::pair<std::string, Zed::Compression>, 5>
        compression_options = 
        {{
            {"Lossless", Zed::Compression::LOSSLESS},
            {"H264", Zed::Compression::H264},
            {"H265", Zed::Compression::H265},
            {"H264, lossless", Zed::Compression::H264_LOSSLESS},
            {"H265, lossless", Zed::Compression::H265_LOSSLESS}
        }};

    Pine::UI::AddCombo("Resolution",
        &parameters.resolution,
        resolution_options);
    Pine::UI::AddCombo("Compression",
        &parameters.compression,
        compression_options);

    Pine::UI::SliderScalar("Target FPS",
        &parameters.fps,
        0,
        100);
    Pine::UI::SliderScalar("Timeout",
        &parameters.timeout,
        -1.0f,
        10.0f);

    ImGui::Checkbox("Image enhancement",
        &parameters.enable_image_enhancement);
    ImGui::Checkbox("Disable self calib.",
        &parameters.disable_self_calibration);
    ImGui::Checkbox("Require sensors",
        &parameters.require_sensors);
    ImGui::Checkbox("Enable depth", &parameters.enable_depth);
}

void DrawCameraSettings(Zed::CameraSettings& settings)
{
    Pine::UI::SliderScalar("Brightness",
        &settings.brightness,
        0,
        8);
    Pine::UI::SliderScalar("Contrast",
        &settings.contrast,
        0,
        8);
    Pine::UI::SliderScalar("Hue", &settings.hue, 0, 11);
    Pine::UI::SliderScalar("Saturation",
        &settings.saturation,
        0,
        8);
    Pine::UI::SliderScalar("Sharpness",
        &settings.sharpness,
        0,
        8);
    Pine::UI::SliderScalar("Gamma",
        &settings.gamma,
        1,
        9);
    Pine::UI::SliderScalar("Gain", &settings.gain, 0, 100);
    Pine::UI::SliderScalar("Exposure",
        &settings.exposure,
        0,
        100);
    Pine::UI::SliderScalar("Whitebalance temp.",
        &settings.whitebalance,
        2800,
        6500);

    ImGui::Checkbox("Auto exposure", &settings.auto_exposure);
    ImGui::Checkbox("Auto whitebalance",
        &settings.auto_whitebalance);
    ImGui::Checkbox("Enable LED", &settings.enable_led);
}

void DrawImageSpecification(Zed::ImageSpecification& specifications)
{
    static const std::array<std::pair<std::string, Zed::View>, 5> 
        view_options = 
        {{
            {"Left", Zed::View::LEFT},
            {"Right", Zed::View::RIGHT},
            {"Left, gray", Zed::View::LEFT_GRAY},
            {"Right, gray", Zed::View::RIGHT_GRAY},
            {"Side by side", Zed::View::SIDE_BY_SIDE}
        }};

    ImGui::InputScalar("Image width", ImGuiDataType_U32, 
        &specifications.width, NULL, NULL);
    ImGui::InputScalar("Image height", ImGuiDataType_U32, 
        &specifications.height, NULL, NULL);
    Pine::UI::AddCombo("View", &specifications.view, view_options);
}
    
}; // namespace Pineapple
