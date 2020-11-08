#pragma once

#include <iostream>
#include <sstream>

namespace Sennet { namespace ZED {

enum class VideoSettings : uint8_t
{ 
	None = 0, Brightness = 1, Contrast = 2, Hue = 3, Saturation = 4, 
	Sharpness = 5, Gain = 6, Exposure = 7, AECAGC = 8, 
	WhitebalanceTemperature = 9, WhitebalanceAuto = 10, LEDStatus = 11
};

enum class View : uint8_t
{ 
	None = 0, Left = 1, Right = 2, LeftGray = 3, RightGray = 4, 
	LeftUnrectified = 5, RightUnrectified = 6, LeftUnrectifiedGray = 7, 
	RightUnrectifiedGray = 8, SideBySide = 9
};

}
}

std::string ToString(const Sennet::ZED::VideoSettings videoSettings);
std::string ToString(const Sennet::ZED::View view);

std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::VideoSettings videoSettings);
std::ostream& operator<<(std::ostream& os, 
	const Sennet::ZED::View view);
