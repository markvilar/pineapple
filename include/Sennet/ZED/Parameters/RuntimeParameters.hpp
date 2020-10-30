#pragma once

#include <iostream>
#include <sstream>

#include "serializer/serializer.h"

namespace Sennet
{

namespace ZED
{

enum class SensingMode : int
{ 
	None = 0, Standard = 1, Fill = 2
};

enum class ReferenceFrame : int
{ 
	None = 0, World = 1, Camera = 2
};

struct RuntimeParametersData
{
public:
	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.sensingMode);
		archive(self.referenceFrame);
		archive(self.enableDepth);
		archive(self.confidenceThreshold);
		archive(self.textureConfidenceThreshold);
	}

public:
	SensingMode sensingMode = SensingMode::Standard;
	ReferenceFrame referenceFrame = ReferenceFrame::Camera;
	bool enableDepth = true;
	int confidenceThreshold = 100;
	int textureConfidenceThreshold = 100;
};

class RuntimeParameters
{
	// Wrapper for sl::RuntimeParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	RuntimeParameters() = default;
	RuntimeParameters(const RuntimeParametersData data) 
		: m_Data(data) {}
	~RuntimeParameters() = default;

	RuntimeParametersData GetData() const { return m_Data; }
	void SetData(const RuntimeParametersData& data) { m_Data = data; }

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, 
		const RuntimeParameters& rp);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Data);
	}


private:
	RuntimeParametersData m_Data;
};

}
}

std::string ToString(const Sennet::ZED::ReferenceFrame referenceFrame);
std::string ToString(const Sennet::ZED::SensingMode sensingMode);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SensingMode sensingMode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::ReferenceFrame referenceFrame);
