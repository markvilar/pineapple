#pragma once

#include <iostream>
#include <sstream>

#include "serializer/serializer.h"

namespace Sennet
{

namespace ZED
{

enum class SVOCompressionMode : int
{ 
	None = 0, Lossless = 1, H264 = 2, H265 = 3
};

struct RecordingParametersData
{
public:
	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.filename);
		archive(self.compressionMode);
		archive(self.targetBitRate);
		archive(self.targetFrameRate);
	}

public:
	std::string filename = "myRecording.svo";
	SVOCompressionMode compressionMode = SVOCompressionMode::H264;
	unsigned int targetBitRate = 0;
	unsigned int targetFrameRate = 0;
};

class RecordingParameters
{
	// Wrapper for sl::RecordingParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	RecordingParameters() = default;
	RecordingParameters(const RecordingParametersData data) 
		: m_Data(data) {}
	~RecordingParameters() = default;

	RecordingParametersData GetData() const { return m_Data; }
	void SetData(const RecordingParametersData& data) { m_Data = data; }

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const RecordingParameters& rp);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Data);
	}

private:
	RecordingParametersData m_Data;
};

}
}

std::string ToString(const Sennet::ZED::SVOCompressionMode compressionMode);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SVOCompressionMode compressionMode);
