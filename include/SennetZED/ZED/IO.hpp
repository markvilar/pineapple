#pragma once

#include <iostream>

#include <sl/Camera.hpp>

std::ostream& operator<<(std::ostream& os, const sl::String& s);

std::ostream& operator<<(std::ostream& os, const sl::InitParameters& params);

std::ostream& operator<<(std::ostream& os, const sl::RuntimeParameters& params);

std::ostream& operator<<(
	std::ostream& os, 
	const sl::RecordingParameters& params
	);

std::ostream& operator<<(std::ostream& os, const sl::CameraInformation& params);

std::ostream& operator<<(std::ostream& os, const sl::Resolution& res);

std::ostream& operator<<(std::ostream& os, const sl::Mat& m);

std::ostream& operator<<(std::ostream& os, sl::Vector2<unsigned char> vs);

std::ostream& operator<<(std::ostream& os, sl::Vector3<unsigned char> vs);

std::ostream& operator<<(std::ostream& os, sl::Vector4<unsigned char> vs);

std::ostream& operator<<(std::ostream& os, sl::Vector2<float> vs);

std::ostream& operator<<(std::ostream& os, sl::Vector3<float> vs);

std::ostream& operator<<(std::ostream& os, sl::Vector4<float> vs);
