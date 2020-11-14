#include "Sennet/ZED/InitParameters.hpp"

namespace Sennet { namespace ZED {

std::string InitParameters::ToString() const
{
	std::stringstream ss;
	ss << "Depth Mode: " << ::ToString(depthMode)
		<< ", Coordinates: " << ::ToString(coordinateSystem)
		<< "/" << ::ToString(coordinateUnits)
		<< ", FPS: " << cameraFPS
		<< ", Resolution: " << ::ToString(resolution);
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const InitParameters& ip)
{
	return os << ip.ToString();
}

}
}

std::string ToString(const Sennet::ZED::CoordinateSystem coordinateSystem)
{
	switch (coordinateSystem)
	{
		case Sennet::ZED::CoordinateSystem::Image: 
			return std::string("Image");
		case Sennet::ZED::CoordinateSystem::LeftHandedYUp: 
			return std::string("LeftHandedYUp");
		case Sennet::ZED::CoordinateSystem::RightHandedYUp:
			return std::string("RightHandedYUp");
		case Sennet::ZED::CoordinateSystem::RightHandedZUp:
			return std::string("RightHandedZUp");
		case Sennet::ZED::CoordinateSystem::LeftHandedZUp:
			return std::string("LeftHandedZUp");
		case Sennet::ZED::CoordinateSystem::RightHandedZUpXForward:
			return std::string("RightHandedZUpXForward");
		default: 
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::DepthMode depthMode)
{
	switch (depthMode)
	{
		case Sennet::ZED::DepthMode::Performance:
			return std::string("Performance");
		case Sennet::ZED::DepthMode::Quality:
			return std::string("Quality");
		case Sennet::ZED::DepthMode::Ultra:
			return std::string("Ultra");
		default:
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::FlipMode flipMode)
{
	switch (flipMode)
	{
		case Sennet::ZED::FlipMode::Off:
			return std::string("Off");
		case Sennet::ZED::FlipMode::On:
			return std::string("On");
		case Sennet::ZED::FlipMode::Auto:
			return std::string("Auto");
		default:
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::Resolution resolution)
{
	switch (resolution)
	{
		case Sennet::ZED::Resolution::HD2K:
			return std::string("HD2K");
		case Sennet::ZED::Resolution::HD1080:
			return std::string("HD1080");
		case Sennet::ZED::Resolution::HD720:
			return std::string("HD720");
		case Sennet::ZED::Resolution::VGA:
			return std::string("VGA");
		default:
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::Unit unit)
{
	switch (unit)
	{
		case Sennet::ZED::Unit::Millimeter:
			return std::string("Millimeter");
		case Sennet::ZED::Unit::Centimeter:
			return std::string("Centimeter");
		case Sennet::ZED::Unit::Meter:
			return std::string("Meter");
		case Sennet::ZED::Unit::Inch:
			return std::string("Inch");
		case Sennet::ZED::Unit::Foot:
			return std::string("Foot");
		default:
			return std::string("None");
	}
}


std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::CoordinateSystem coordinateSystem)
{
	return os << ToString(coordinateSystem);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::DepthMode depthMode)
{
	return os << ToString(depthMode);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Resolution resolution)
{
	return os << ToString(resolution);
}

std::ostream& operator<<(std::ostream& os, const Sennet::ZED::Unit unit)
{
	return os << ToString(unit);
}
