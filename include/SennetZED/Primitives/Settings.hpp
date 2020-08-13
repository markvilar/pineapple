#pragma once
#include <Sennet/Sennet.hpp>

namespace Sennet
{

namespace ZED
{

enum class CoordinateSystem
{
	None = 0, Image, LeftHandedYUp, RightHandedYUp, RightHandedZUp,
	LeftHandedZUp, RightHandedZUpXForward
};

enum class DepthMode 
{ 
	None = 0, Performance, Quality, Ultra
};

enum class ReferenceFrame 
{ 
	None = 0, World, Camera 
};

enum class Resolution 
{ 
	None = 0, HD2K, HD1080, HD720, VGA 
};

enum class SVOCompressionMode
{ 
	None = 0, Lossless, H264, H265 
};

enum class SensingMode 
{ 
	None = 0, Standard, Fill 
};

enum class Unit 
{ 
	None = 0, Millimeter, Centimeter, Meter, Inch, Foot 
};

enum class VideoSettings
{ 
	None = 0, Brightness, Contrast, Hue, Saturation, Sharpness, Gain, 
	Exposure, AECAGC, WhitebalanceTemperature, WhitebalanceAuto,
	LEDStatus
};

enum class View 
{ 
	None = 0, Left, Right, LeftGray, RightGray, LeftUnrectified,
	RightUnrectified, LeftUnrectifiedGray, RightUnrectifiedGray,
	SideBySide
};

struct InitParametersData
{
public:
	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.depthMode);
		archive(self.coordinateUnits);
		archive(self.coordinateSystem);
		archive(self.depthStabilization);
		archive(self.depthStabilization);
		archive(self.depthStabilization);
		archive(self.depthStabilization);

		archive(self.resolution);
		archive(self.cameraFPS);
		archive(self.enableImageEnhancement);
		archive(self.disableSelfCalibration);
		archive(self.enableVerboseSDK);
		archive(self.requireSensors);
	}

public:
	// Depth related members.
	DepthMode depthMode = DepthMode::Ultra;
	Unit coordinateUnits = Unit::Millimeter;
	CoordinateSystem coordinateSystem = CoordinateSystem::Image;
	int depthStabilization = 1;
	float minDepth = -1;
	float maxDepth = -1;
	bool enableRightSideDepth = false;

	// Generic members.
	Resolution resolution = Resolution::HD720;
	int cameraFPS = 0;
	bool enableImageEnhancement = true;
	bool disableSelfCalibration = false;
	bool enableVerboseSDK = false;
	bool requireSensors= false;
};

class InitParameters
{
	// Wrapper for sl::InitParameters. Neglects functionality of the
	// Stereolabs SDK that is considered unimportant for recording.
public:
	InitParameters() = default;
	InitParameters(const InitParametersData& data) : m_Data(data) {}
	~InitParameters() = default;

	InitParametersData GetData() const { return m_Data; }
	void SetData(const InitParametersData& data) { m_Data = data; }

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& os, const InitParameters& ip);

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		archive(self.m_Data);
	}

private:
	InitParametersData m_Data;
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
	RecordingParameters(const RecordingParametersData& data) 
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
	RuntimeParameters(const RuntimeParametersData& data) 
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

std::string ToString(const Sennet::ZED::CoordinateSystem coordinateSystem);
std::string ToString(const Sennet::ZED::DepthMode depthMode);
std::string ToString(const Sennet::ZED::ReferenceFrame referenceFrame);
std::string ToString(const Sennet::ZED::Resolution resolution);
std::string ToString(const Sennet::ZED::SVOCompressionMode compressionMode);
std::string ToString(const Sennet::ZED::SensingMode sensingMode);
std::string ToString(const Sennet::ZED::Unit unit);
std::string ToString(const Sennet::ZED::VideoSettings videoSettings);
std::string ToString(const Sennet::ZED::View view);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::CoordinateSystem coordinateSystem);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::DepthMode depthMode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::ReferenceFrame referenceFrame);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Resolution resolution);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SVOCompressionMode compressionMode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::SensingMode sensingMode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Unit unit);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::VideoSettings videoSettings);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::View view);
