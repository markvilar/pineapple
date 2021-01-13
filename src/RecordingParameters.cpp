#include "Sennet-ZED/RecordingParameters.hpp"

namespace Sennet { namespace ZED {

std::string RecordingParameters::ToString() const
{
	std::stringstream ss;
	ss << "Filename: " << filename
		<< ", Compression Mode: " << ::ToString(compressionMode);
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const RecordingParameters& rp)
{
	return os << rp.ToString();
}

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

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SVOCompressionMode compressionMode)
{
	return os << ToString(compressionMode);
}
