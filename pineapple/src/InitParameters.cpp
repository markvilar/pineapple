#include "Pineapple/InitParameters.hpp"

namespace Pineapple
{

std::string InitParameters::ToString() const
{
    std::stringstream ss;
    ss << "Depth Mode: " << ::ToString(depthMode)
       << ", Coordinates: " << ::ToString(coordinateSystem) << "/"
       << ::ToString(coordinateUnits) << ", FPS: " << cameraFPS
       << ", Resolution: " << ::ToString(resolution);
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const InitParameters& ip)
{
    return os << ip.ToString();
}

} // namespace Pineapple

std::string ToString(const Pineapple::CoordinateSystem coordinateSystem)
{
    switch (coordinateSystem)
    {
    case Pineapple::CoordinateSystem::Image:
        return std::string("Image");
    case Pineapple::CoordinateSystem::LeftHandedYUp:
        return std::string("LeftHandedYUp");
    case Pineapple::CoordinateSystem::RightHandedYUp:
        return std::string("RightHandedYUp");
    case Pineapple::CoordinateSystem::RightHandedZUp:
        return std::string("RightHandedZUp");
    case Pineapple::CoordinateSystem::LeftHandedZUp:
        return std::string("LeftHandedZUp");
    case Pineapple::CoordinateSystem::RightHandedZUpXForward:
        return std::string("RightHandedZUpXForward");
    default:
        return std::string("None");
    }
}

std::string ToString(const Pineapple::DepthMode depthMode)
{
    switch (depthMode)
    {
    case Pineapple::DepthMode::Performance:
        return std::string("Performance");
    case Pineapple::DepthMode::Quality:
        return std::string("Quality");
    case Pineapple::DepthMode::Ultra:
        return std::string("Ultra");
    default:
        return std::string("None");
    }
}

std::string ToString(const Pineapple::FlipMode flipMode)
{
    switch (flipMode)
    {
    case Pineapple::FlipMode::Off:
        return std::string("Off");
    case Pineapple::FlipMode::On:
        return std::string("On");
    case Pineapple::FlipMode::Auto:
        return std::string("Auto");
    default:
        return std::string("None");
    }
}

std::string ToString(const Pineapple::Resolution resolution)
{
    switch (resolution)
    {
    case Pineapple::Resolution::HD2K:
        return std::string("HD2K");
    case Pineapple::Resolution::HD1080:
        return std::string("HD1080");
    case Pineapple::Resolution::HD720:
        return std::string("HD720");
    case Pineapple::Resolution::VGA:
        return std::string("VGA");
    default:
        return std::string("None");
    }
}

std::string ToString(const Pineapple::Unit unit)
{
    switch (unit)
    {
    case Pineapple::Unit::Millimeter:
        return std::string("Millimeter");
    case Pineapple::Unit::Centimeter:
        return std::string("Centimeter");
    case Pineapple::Unit::Meter:
        return std::string("Meter");
    case Pineapple::Unit::Inch:
        return std::string("Inch");
    case Pineapple::Unit::Foot:
        return std::string("Foot");
    default:
        return std::string("None");
    }
}

std::ostream& operator<<(
    std::ostream& os, const Pineapple::CoordinateSystem coordinateSystem)
{
    return os << ToString(coordinateSystem);
}

std::ostream& operator<<(std::ostream& os, const Pineapple::DepthMode depthMode)
{
    return os << ToString(depthMode);
}

std::ostream& operator<<(
    std::ostream& os, const Pineapple::Resolution resolution)
{
    return os << ToString(resolution);
}

std::ostream& operator<<(std::ostream& os, const Pineapple::Unit unit)
{
    return os << ToString(unit);
}
