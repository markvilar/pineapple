#pragma once

#include <iostream>
#include <sstream>

namespace Pineapple
{

enum class SensingMode : uint8_t
{
    None = 0,
    Standard = 1,
    Fill = 2
};

enum class ReferenceFrame : uint8_t
{
    None = 0,
    World = 1,
    Camera = 2
};

class RuntimeParameters
{
public:
    RuntimeParameters() = default;
    ~RuntimeParameters() = default;

    std::string ToString() const;
    friend std::ostream& operator<<(
        std::ostream& os, const RuntimeParameters& rp);

public:
    SensingMode sensingMode = SensingMode::Standard;
    ReferenceFrame referenceFrame = ReferenceFrame::Camera;
    bool enableDepth = true;
    uint32_t confidenceThreshold = 100;
    uint32_t textureConfidenceThreshold = 100;
};

std::string ToString(const ReferenceFrame& referenceFrame);
std::string ToString(const SensingMode& sensingMode);

std::ostream& operator<<(std::ostream& os, const SensingMode& sensingMode);
std::ostream& operator<<(
    std::ostream& os, const ReferenceFrame& referenceFrame);

} // namespace Pineapple
