#include "Sennet-ZED/RuntimeParameters.hpp"

namespace Sennet { namespace ZED {

std::string RuntimeParameters::ToString() const
{
	std::stringstream ss;
	ss << "Sensing Mode: " << Sennet::ZED::ToString(sensingMode)
		<< ", Reference Frame: " << Sennet::ZED::ToString(referenceFrame)
		<< ", Depth Enabled: " << enableDepth;
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RuntimeParameters& rp)
{
	return os << rp.ToString();
}

std::string ToString(const ReferenceFrame& referenceFrame)
{
	switch (referenceFrame)
	{
		case ReferenceFrame::World:
			return std::string("World");
		case ReferenceFrame::Camera:
			return std::string("Camera");
		default:
			return std::string("None");
	}
}

std::string ToString(const SensingMode& sensingMode)
{
	switch (sensingMode)
	{
		case SensingMode::Standard:
			return std::string("Standard");
		case SensingMode::Fill:
			return std::string("Fill");
		default:
			return std::string("None");
	}
}

std::ostream& operator<<(std::ostream& os, const ReferenceFrame& referenceFrame)
{
	return os << ToString(referenceFrame);
}

std::ostream& operator<<(std::ostream& os, const SensingMode& sensingMode)
{
	return os << ToString(sensingMode);
}

}}
