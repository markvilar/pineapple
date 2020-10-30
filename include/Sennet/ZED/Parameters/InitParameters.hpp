#pragma once

#include <iostream>
#include <sstream>

#include "serializer/serializer.h"

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

enum class Resolution : int
{ 
	None = 0, HD2K = 1, HD1080 = 2, HD720 = 3, VGA = 4
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

}
}

std::string ToString(const Sennet::ZED::CoordinateSystem coordinateSystem);
std::string ToString(const Sennet::ZED::DepthMode depthMode);
std::string ToString(const Sennet::ZED::Resolution resolution);
std::string ToString(const Sennet::ZED::Unit unit);
std::string ToString(const Sennet::ZED::VideoSettings videoSettings);
std::string ToString(const Sennet::ZED::View view);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::CoordinateSystem coordinateSystem);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::DepthMode depthMode);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Resolution resolution);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::Unit unit);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::VideoSettings videoSettings);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::View view);
