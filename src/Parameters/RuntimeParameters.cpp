#include "Sennet/ZED/Parameters/RuntimeParameters.hpp"

namespace Sennet
{

namespace ZED
{

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

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::ReferenceFrame referenceFrame)
{
	return os << ToString(referenceFrame);
}

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SensingMode sensingMode)
{
	return os << ToString(sensingMode);
}
