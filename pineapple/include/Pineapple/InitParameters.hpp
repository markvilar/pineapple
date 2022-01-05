#pragma once

#include <iostream>
#include <sstream>

namespace Pineapple
{

enum class CoordinateSystem : uint8_t
{
    None = 0,
    Image = 1,
    LeftHandedYUp = 2,
    RightHandedYUp = 3,
    RightHandedZUp = 4,
    LeftHandedZUp = 5,
    RightHandedZUpXForward = 6
};

enum class DepthMode : uint8_t
{
    None = 0,
    Performance = 1,
    Quality = 2,
    Ultra = 3
};

enum class FlipMode : uint8_t
{
    None = 0,
    Off = 1,
    On = 2,
    Auto = 3
};

enum class Resolution : uint8_t
{
    None = 0,
    HD2K = 1,
    HD1080 = 2,
    HD720 = 3,
    VGA = 4
};

enum class Unit : uint8_t
{
    None = 0,
    Millimeter = 1,
    Centimeter = 2,
    Meter = 3,
    Inch = 4,
    Foot = 5
};

class InitParameters
{
public:
    InitParameters() = default;
    ~InitParameters() = default;

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream& os, const InitParameters& ip);

public:
    // Depth related members.
    DepthMode depthMode = DepthMode::Ultra;
    Unit coordinateUnits = Unit::Millimeter;
    CoordinateSystem coordinateSystem = CoordinateSystem::Image;
    bool enableDepthStabilization = true;
    float minDepth = -1;
    float maxDepth = -1;
    bool enableRightSideDepth = false;

    // Generic members.
    Resolution resolution = Resolution::HD720;
    FlipMode flipMode = FlipMode::Auto;
    uint32_t cameraFPS = 0;
    bool enableImageEnhancement = true;
    bool disableSelfCalibration = false;
    bool enableVerboseSDK = false;
    bool requireSensors = false;
};

} // namespace Pineapple

std::string ToString(const Pineapple::CoordinateSystem coordinateSystem);
std::string ToString(const Pineapple::DepthMode depthMode);
std::string ToString(const Pineapple::FlipMode flipMode);
std::string ToString(const Pineapple::Resolution resolution);
std::string ToString(const Pineapple::Unit unit);

std::ostream& operator<<(
    std::ostream& os, const Pineapple::CoordinateSystem coordinateSystem);
std::ostream& operator<<(
    std::ostream& os, const Pineapple::DepthMode depthMode);
std::ostream& operator<<(std::ostream& os, const Pineapple::FlipMode flipMode);
std::ostream& operator<<(
    std::ostream& os, const Pineapple::Resolution resolution);
std::ostream& operator<<(std::ostream& os, const Pineapple::Unit unit);
