#pragma once

#include <Pine/Pine.hpp>

#include "Pineapple/CameraParameters.hpp"
#include "Pineapple/CameraSettings.hpp"

namespace Pineapple
{

struct PanelLayout
{
    Pine::Vec2 Position{};
    Pine::Vec2 Size{};

public:
    PanelLayout() = default;
    PanelLayout(const PanelLayout&) = default;
    PanelLayout(PanelLayout&&) = default;

    PanelLayout(const Pine::Vec2& position, const Pine::Vec2& size)
        : Position(position), Size(size)
    {
    }

    PanelLayout& operator=(const PanelLayout&) = default;
    PanelLayout& operator=(PanelLayout&&) = default;
};

void DrawCameraParameters(ZED::CameraParameters& parameters);
void DrawCameraSettings(ZED::CameraSettings& settings);

}; // namespace Pineapple
