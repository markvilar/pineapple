#include <SennetZED/Primitives/Settings.hpp>

namespace Sennet
{

namespace ZED
{

std::string InitParameters::ToString() const
{
	std::stringstream ss;
	ss << "Depth Mode: " << ::ToString(m_Data.depthMode)
		<< ", Coordinates: " << ::ToString(m_Data.coordinateSystem)
		<< "/" << ::ToString(m_Data.coordinateUnits)
		<< ", FPS: " << m_Data.cameraFPS
		<< ", Resolution: " << ::ToString(m_Data.resolution);
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const InitParameters& ip)
{
	return os << ip.ToString();
}

std::string RecordingParameters::ToString() const
{
	std::stringstream ss;
	ss << "Filename: " << m_Data.filename
		<< ", Compression Mode: " << ::ToString(m_Data.compressionMode);
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RecordingParameters& rp)
{
	return os << rp.ToString();
}

std::string RuntimeParameters::ToString() const
{
	std::stringstream ss;
	ss << "Sensing Mode: " << ::ToString(m_Data.sensingMode)
		<< ", Reference Frame: " << ::ToString(m_Data.referenceFrame)
		<< ", Depth Enabled: " << m_Data.enableDepth;
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RuntimeParameters& rp)
{
	return os << rp.ToString();
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

std::string ToString(const Sennet::ZED::ReferenceFrame referenceFrame)
{
	switch (referenceFrame)
	{
		case Sennet::ZED::ReferenceFrame::World:
			return std::string("World");
		case Sennet::ZED::ReferenceFrame::Camera:
			return std::string("Camera");
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

std::string ToString(const Sennet::ZED::SVOCompressionMode compressionMode)
{
	switch (compressionMode)
	{
		case Sennet::ZED::SVOCompressionMode::Lossless:
			return std::string("Lossless");
		case Sennet::ZED::SVOCompressionMode::H264:
			return std::string("H264");
		case Sennet::ZED::SVOCompressionMode::H265:
			return std::string("H265");
		default:
			return std::string("None");
	}
}

std::string ToString(const Sennet::ZED::SensingMode sensingMode)
{
	switch (sensingMode)
	{
		case Sennet::ZED::SensingMode::Standard:
			return std::string("Standard");
		case Sennet::ZED::SensingMode::Fill:
			return std::string("Fill");
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
	const Sennet::ZED::ReferenceFrame referenceFrame)
{
	return os << ToString(referenceFrame);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Resolution resolution)
{
	return os << ToString(resolution);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SVOCompressionMode compressionMode)
{
	return os << ToString(compressionMode);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SensingMode sensingMode)
{
	return os << ToString(sensingMode);
}

std::ostream& operator<<(std::ostream& os, const Sennet::ZED::Unit unit)
{
	return os << ToString(unit);
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
