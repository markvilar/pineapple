#pragma once

#include <iostream>
#include <sstream>

namespace Sennet { namespace ZED {

enum class SVOCompressionMode : uint8_t
{ 
	None = 0, Lossless = 1, H264 = 2, H265 = 3
};

class RecordingParameters
{
	// Wrapper for sl::RecordingParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	RecordingParameters() = default;
	~RecordingParameters() = default;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const RecordingParameters& rp);

public:
	std::string filename = "myRecording.svo";
	SVOCompressionMode compressionMode = SVOCompressionMode::H264;
	unsigned int targetBitRate = 0;
	unsigned int targetFrameRate = 0;
};

}
}

std::string ToString(const Sennet::ZED::SVOCompressionMode compressionMode);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SVOCompressionMode compressionMode);
