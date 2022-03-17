#include "Pineapple/UserInterface.hpp"

namespace Pineapple 
{

void DrawCameraParameters(ZED::CameraParameters& parameters)
{
    const std::array<std::pair<std::string, ZED::Resolution>, 4>
        resolutionOptions = {
            std::make_pair("HD2K", ZED::Resolution::HD2K),
            std::make_pair("HD1080", ZED::Resolution::HD1080),
            std::make_pair("HD720", ZED::Resolution::HD720),
            std::make_pair("VGA", ZED::Resolution::VGA)};

    const std::array<std::pair<std::string, ZED::CompressionMode>, 3>
        compressionOptions = {
            std::make_pair("Lossless", ZED::CompressionMode::LOSSLESS),
            std::make_pair("H264", ZED::CompressionMode::H264),
            std::make_pair("H265", ZED::CompressionMode::H265)};

    Pine::UI::AddCombo("Resolution",
        &parameters.CameraResolution,
        resolutionOptions);
    Pine::UI::AddCombo("Compression",
        &parameters.Compression,
        compressionOptions);

    Pine::UI::SliderScalar("Target FPS",
        &parameters.CameraFPS,
        0,
        100);
    Pine::UI::SliderScalar("Timeout",
        &parameters.OpenTimeout,
        -1.0f,
        10.0f);

    ImGui::Checkbox("Image enhancement",
        &parameters.EnableImageEnhancement);
    ImGui::Checkbox("Disable self calib.",
        &parameters.DisableSelfCalibration);
    ImGui::Checkbox("Require sensors",
        &parameters.RequireSensors);
    ImGui::Checkbox("Enable depth", &parameters.EnableDepth);
}

void DrawCameraSettings(ZED::CameraSettings& settings)
{
    Pine::UI::SliderScalar("Brightness",
        &settings.Brightness,
        0,
        8);
    Pine::UI::SliderScalar("Contrast",
        &settings.Contrast,
        0,
        8);
    Pine::UI::SliderScalar("Hue", &settings.Hue, 0, 11);
    Pine::UI::SliderScalar("Saturation",
        &settings.Saturation,
        0,
        8);
    Pine::UI::SliderScalar("Sharpness",
        &settings.Sharpness,
        0,
        8);
    Pine::UI::SliderScalar("Gamma",
        &settings.Gamma,
        1,
        9);
    Pine::UI::SliderScalar("Gain", &settings.Gain, 0, 100);
    Pine::UI::SliderScalar("Exposure",
        &settings.Exposure,
        0,
        100);
    Pine::UI::SliderScalar("Whitebalance temp.",
        &settings.Whitebalance,
        2800,
        6500);

    ImGui::Checkbox("Auto exposure", &settings.AutoExposure);
    ImGui::Checkbox("Auto whitebalance",
        &settings.AutoWhitebalance);
    ImGui::Checkbox("Enable LED ", &settings.EnableLED);
}

void DrawImageConfiguration(ZED::ImageConfiguration& config)
{
    const std::array<std::pair<std::string, ZED::View>, 5> viewOptions = 
        {
            std::make_pair("Left", ZED::View::LEFT),
            std::make_pair("Right", ZED::View::RIGHT),
            std::make_pair("Left, gray", ZED::View::LEFT_GRAY),
            std::make_pair("Right, gray", ZED::View::RIGHT_GRAY),
            std::make_pair("Side by side", ZED::View::SIDE_BY_SIDE)
        };

    ImGui::InputScalar("Image width", ImGuiDataType_U32, 
        &config.Width, NULL, NULL);
    ImGui::InputScalar("Image height", ImGuiDataType_U32, 
        &config.Height, NULL, NULL);
    Pine::UI::AddCombo("View",
        &config.Type,
        viewOptions);
}

    
}; // namespace Pineapple
