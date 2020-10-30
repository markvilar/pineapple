#pragma once

#include <memory>

#include <sl/Camera.hpp>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Parameters/InitParameters.hpp"
#include "Sennet/ZED/Parameters/RecordingParameters.hpp"
#include "Sennet/ZED/Parameters/RuntimeParameters.hpp"

// Conversion function from Sennet::ZED types to sl types.
sl::VIEW SennetToStereolabs(const Sennet::ZED::View& view);
sl::RESOLUTION SennetToStereolabs(const Sennet::ZED::Resolution& resolution);
sl::VIDEO_SETTINGS SennetToStereolabs(
	const Sennet::ZED::VideoSettings& videoSettings);
sl::DEPTH_MODE SennetToStereolabs(const Sennet::ZED::DepthMode& depthMode);
sl::UNIT SennetToStereolabs(const Sennet::ZED::Unit& unit);
sl::SVO_COMPRESSION_MODE SennetToStereolabs(
	const Sennet::ZED::SVOCompressionMode& compressionMode);
sl::SENSING_MODE SennetToStereolabs(
	const Sennet::ZED::SensingMode& sensingMode);
sl::REFERENCE_FRAME SennetToStereolabs(
	const Sennet::ZED::ReferenceFrame& referenceFrame);
sl::COORDINATE_SYSTEM SennetToStereolabs(
	const Sennet::ZED::CoordinateSystem& coordinateSystem);

// Conversion function from Sennet::ZED classes to sl classes.
Sennet::Ref<sl::Mat> SennetToStereolabs(const Sennet::Ref<Sennet::Image>& image);
sl::InitParameters SennetToStereolabs(
	const Sennet::ZED::InitParameters& initParameters);
sl::RecordingParameters SennetToStereolabs(
	const Sennet::ZED::RecordingParameters& recordingParameters);
sl::RuntimeParameters SennetToStereolabs(
	const Sennet::ZED::RuntimeParameters& runtimeParameters);

// Conversion function from sl types to Sennet::ZED types.
Sennet::ZED::View StereolabsToSennet(const sl::VIEW& view);
Sennet::ZED::Resolution StereolabsToSennet(const sl::RESOLUTION& resolution);
Sennet::ZED::VideoSettings StereolabsToSennet(
	const sl::VIDEO_SETTINGS& videoSettings);
Sennet::ZED::DepthMode StereolabsToSennet(const sl::DEPTH_MODE& depthMode);
Sennet::ZED::Unit StereolabsToSennet(const sl::UNIT& unit);
Sennet::ZED::SVOCompressionMode StereolabsToSennet(
	const sl::SVO_COMPRESSION_MODE& compressionMode);
Sennet::ZED::SensingMode StereolabsToSennet(const sl::SENSING_MODE& sensingMode);
Sennet::ZED::ReferenceFrame StereolabsToSennet(
	const sl::REFERENCE_FRAME& referenceFrame);
Sennet::ZED::CoordinateSystem StereolabsToSennet(
	const sl::COORDINATE_SYSTEM& coordinateSystem);

// Conversion function from sl classes to Sennet::ZED classes.
Sennet::Ref<Sennet::Image> StereolabsToSennet(
	const Sennet::Ref<sl::Mat>& mat);
Sennet::ZED::InitParameters StereolabsToSennet(
	const sl::InitParameters& initParameters);
Sennet::ZED::RecordingParameters StereolabsToSennet(
	const sl::RecordingParameters& recordingParameters);
Sennet::ZED::RuntimeParameters StereolabsToSennet(
	const sl::RuntimeParameters& runtimeParameters);
