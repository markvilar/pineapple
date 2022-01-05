#include "Pineapple/RecordingParameters.hpp"

namespace Pineapple
{

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

} // namespace Pineapple

std::string ToString(const Pineapple::SVOCompressionMode compressionMode)
{
    switch (compressionMode)
    {
    case Pineapple::SVOCompressionMode::Lossless:
        return std::string("Lossless");
    case Pineapple::SVOCompressionMode::H264:
        return std::string("H264");
    case Pineapple::SVOCompressionMode::H265:
        return std::string("H265");
    default:
        return std::string("None");
    }
}

std::ostream& operator<<(
    std::ostream& os, const Pineapple::SVOCompressionMode compressionMode)
{
    return os << ToString(compressionMode);
}
