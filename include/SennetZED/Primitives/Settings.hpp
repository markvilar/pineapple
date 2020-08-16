#pragma once
#include <Sennet/Sennet.hpp>

namespace Sennet
{

namespace ZED
{

enum class RecorderState : int
{
	None 	= 0,
	Idle 	= 1,
	Standby = 2,
	Record 	= 3
};

enum class CoordinateSystem : int
{
	None = 0, Image = 1, LeftHandedYUp = 2, RightHandedYUp = 3, 
	RightHandedZUp = 4, LeftHandedZUp = 5, RightHandedZUpXForward = 6
};

enum class DepthMode : int
{ 
	None = 0, Performance = 1, Quality = 2, Ultra = 3
};

enum class ReferenceFrame : int
{ 
	None = 0, World = 1, Camera = 2
};

enum class Resolution : int
{ 
	None = 0, HD2K = 1, HD1080 = 2, HD720 = 3, VGA = 4
};

enum class SVOCompressionMode : int
{ 
	None = 0, Lossless = 1, H264 = 2, H265 = 3
};

enum class SensingMode : int
{ 
	None = 0, Standard = 1, Fill = 2
};

enum class Unit : int
{ 
	None = 0, Millimeter = 1, Centimeter = 2, Meter = 3, Inch = 4, Foot = 5
};

enum class VideoSettings : int
{ 
	None = 0, Brightness = 1, Contrast = 2, Hue = 3, Saturation = 4, 
	Sharpness = 5, Gain = 6, Exposure = 7, AECAGC = 8, 
	WhitebalanceTemperature = 9, WhitebalanceAuto = 10, LEDStatus = 11
};

enum class View : int
{ 
	None = 0, Left = 1, Right = 2, LeftGray = 3, RightGray = 4, 
	LeftUnrectified = 5, RightUnrectified = 6, LeftUnrectifiedGray = 7, 
	RightUnrectifiedGray = 8, SideBySide = 9
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
		archive(self.enableDepthStabilization);
		archive(self.minDepth);
		archive(self.maxDepth);
		archive(self.enableRightSideDepth);

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
	bool enableDepthStabilization = true;
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
	InitParameters(const InitParametersData data) : m_Data(data) {}
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
