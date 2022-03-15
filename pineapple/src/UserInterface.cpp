#include "Pineapple/UserInterface.hpp"

namespace Pineapple 
{

void DrawCameraParameters(ZED::CameraParameters& parameters)
{
    const std::array<std::pair<std::string, ZED::FlipMode>, 3>
        cameraFlipOptions = {std::make_pair("Off", ZED::FlipMode::OFF),
            std::make_pair("On", ZED::FlipMode::ON),
            std::make_pair("Auto", ZED::FlipMode::AUTO)};

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

    Pine::UI::AddCombo("Flip mode",
        &parameters.CameraFlip,
        cameraFlipOptions);
    Pine::UI::AddCombo("Resolution",
        &parameters.CameraResolution,
        resolutionOptions);
    Pine::UI::AddCombo("Compression",
        &parameters.Compression,
        compressionOptions);

    Pine::UI::AddEmptySpace(0.0f, 20.0f);

    Pine::UI::SliderScalar("Target FPS",
        &parameters.CameraFPS,
        0,
        100);
    Pine::UI::SliderScalar("Timeout",
        &parameters.OpenTimeout,
        -1.0f,
        10.0f);

    Pine::UI::AddEmptySpace(0.0f, 20.0f);

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
    Pine::UI::SliderScalar("Gain", &settings.Gain, 0, 100);
    Pine::UI::SliderScalar("Exposure",
        &settings.Exposure,
        0,
        100);
    Pine::UI::SliderScalar("Whitebalance temp.",
        &settings.Whitebalance,
        2800,
        6500);

    Pine::UI::AddEmptySpace(0.0f, 20.0f);

    ImGui::Checkbox("Auto exposure", &settings.AutoExposure);
    ImGui::Checkbox("Auto whitebalance",
        &settings.AutoWhitebalance);
    ImGui::Checkbox("Enable LED ", &settings.EnableLED);
}
    
}; // namespace Pineapple
