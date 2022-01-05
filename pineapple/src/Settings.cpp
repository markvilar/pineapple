#include "Pineapple/Settings.hpp"

namespace Pineapple
{

std::string ToString(const VideoSettings& videoSettings)
{
    switch (videoSettings)
    {
    case VideoSettings::Brightness:
        return std::string("Brightness");
    case VideoSettings::Contrast:
        return std::string("Contrast");
    case VideoSettings::Hue:
        return std::string("Hue");
    case VideoSettings::Saturation:
        return std::string("Saturation");
    case VideoSettings::Sharpness:
        return std::string("Sharpness");
    case VideoSettings::Gain:
        return std::string("Gain");
    case VideoSettings::Exposure:
        return std::string("Exposure");
    case VideoSettings::AECAGC:
        return std::string("AECAGC");
    case VideoSettings::WhitebalanceTemperature:
        return std::string("WhitebalanceTemperature");
    case VideoSettings::WhitebalanceAuto:
        return std::string("WhitebalanceAuto");
    case VideoSettings::LEDStatus:
        return std::string("LEDStatus");
    default:
        return std::string("None");
    }
}

std::string ToString(const View& v)
{
    switch (v)
    {
    case View::Left:
        return std::string("Left");
    case View::Right:
        return std::string("Right");
    case View::LeftGray:
        return std::string("LeftGray");
    case View::RightGray:
        return std::string("RightGray");
    case View::LeftUnrectified:
        return std::string("LeftUnrectified");
    case View::RightUnrectified:
        return std::string("RightUnrectified");
    case View::LeftUnrectifiedGray:
        return std::string("LeftUnrectifiedGray");
    case View::RightUnrectifiedGray:
        return std::string("RightUnrectifiedGray");
    case View::SideBySide:
        return std::string("SideBySide");
    default:
        return std::string("None");
    }
}

std::ostream& operator<<(std::ostream& os, const VideoSettings& videoSettings)
{
    return os << ToString(videoSettings);
}

std::ostream& operator<<(std::ostream& os, const View& view)
{
    return os << ToString(view);
}

} // namespace Pineapple
