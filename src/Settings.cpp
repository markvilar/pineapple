#include "Sennet-ZED/Settings.hpp"

std::string ToString(const Sennet::ZED::VideoSettings videoSettings)
{
	switch (videoSettings)
	{
		case Sennet::ZED::VideoSettings::Brightness:
			return std::string("Brightness");
		case Sennet::ZED::VideoSettings::Contrast:
			return std::string("Contrast");
		case Sennet::ZED::VideoSettings::Hue:
			return std::string("Hue");
		case Sennet::ZED::VideoSettings::Saturation:
			return std::string("Saturation");
		case Sennet::ZED::VideoSettings::Sharpness:
			return std::string("Sharpness");
		case Sennet::ZED::VideoSettings::Gain:
			return std::string("Gain");
		case Sennet::ZED::VideoSettings::Exposure:
			return std::string("Exposure");
		case Sennet::ZED::VideoSettings::AECAGC:
			return std::string("AECAGC");
		case Sennet::ZED::VideoSettings::WhitebalanceTemperature:
			return std::string("WhitebalanceTemperature");
		case Sennet::ZED::VideoSettings::WhitebalanceAuto:
			return std::string("WhitebalanceAuto");
		case Sennet::ZED::VideoSettings::LEDStatus:
			return std::string("LEDStatus");
		default:
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::View v)
{
	switch (v)
	{
		case Sennet::ZED::View::Left:
			return std::string("Left");
		case Sennet::ZED::View::Right:
			return std::string("Right");
		case Sennet::ZED::View::LeftGray:
			return std::string("LeftGray");
		case Sennet::ZED::View::RightGray:
			return std::string("RightGray");
		case Sennet::ZED::View::LeftUnrectified:
			return std::string("LeftUnrectified");
		case Sennet::ZED::View::RightUnrectified:
			return std::string("RightUnrectified");
		case Sennet::ZED::View::LeftUnrectifiedGray:
			return std::string("LeftUnrectifiedGray");
		case Sennet::ZED::View::RightUnrectifiedGray:
			return std::string("RightUnrectifiedGray");
		case Sennet::ZED::View::SideBySide:
			return std::string("SideBySide");
		default:
			return std::string("None");
	}
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::VideoSettings videoSettings)
{
	return os << ToString(videoSettings);
}

std::ostream& operator<<(std::ostream& os, const Sennet::ZED::View view)
{
	return os << ToString(view);
}
