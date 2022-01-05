#pragma once

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "sl/Camera.hpp"

//#include "Pine/Pine.hpp"

#include "Pineapple/InitParameters.hpp"
#include "Pineapple/RecordingParameters.hpp"
#include "Pineapple/RuntimeParameters.hpp"
#include "Pineapple/Settings.hpp"

// Conversion function from Pineapple types to sl types.
sl::VIEW PineToStereolabs(const Pineapple::View& view);
sl::RESOLUTION PineToStereolabs(const Pineapple::Resolution& resolution);
sl::VIDEO_SETTINGS PineToStereolabs(
    const Pineapple::VideoSettings& videoSettings);
sl::DEPTH_MODE PineToStereolabs(const Pineapple::DepthMode& depthMode);
sl::FLIP_MODE PineToStereolabs(const Pineapple::FlipMode& flipMode);
sl::UNIT PineToStereolabs(const Pineapple::Unit& unit);
sl::SVO_COMPRESSION_MODE PineToStereolabs(
    const Pineapple::SVOCompressionMode& compressionMode);
sl::SENSING_MODE PineToStereolabs(const Pineapple::SensingMode& sensingMode);
sl::REFERENCE_FRAME PineToStereolabs(
    const Pineapple::ReferenceFrame& referenceFrame);
sl::COORDINATE_SYSTEM PineToStereolabs(
    const Pineapple::CoordinateSystem& coordinateSystem);

// Conversion function from Pineapple classes to sl classes.
sl::InitParameters PineToStereolabs(
    const Pineapple::InitParameters& initParameters);
sl::RecordingParameters PineToStereolabs(
    const Pineapple::RecordingParameters& recordingParameters);
sl::RuntimeParameters PineToStereolabs(
    const Pineapple::RuntimeParameters& runtimeParameters);

// Conversion function from sl types to Pineapple types.
Pineapple::View StereolabsToPine(const sl::VIEW& view);
Pineapple::Resolution StereolabsToPine(const sl::RESOLUTION& resolution);
Pineapple::VideoSettings StereolabsToPine(
    const sl::VIDEO_SETTINGS& videoSettings);
Pineapple::DepthMode StereolabsToPine(const sl::DEPTH_MODE& depthMode);
Pineapple::FlipMode StereolabsToPine(const int flipMode);
Pineapple::Unit StereolabsToPine(const sl::UNIT& unit);
Pineapple::SVOCompressionMode StereolabsToPine(
    const sl::SVO_COMPRESSION_MODE& compressionMode);
Pineapple::SensingMode StereolabsToPine(const sl::SENSING_MODE& sensingMode);
Pineapple::ReferenceFrame StereolabsToPine(
    const sl::REFERENCE_FRAME& referenceFrame);
Pineapple::CoordinateSystem StereolabsToPine(
    const sl::COORDINATE_SYSTEM& coordinateSystem);

// Conversion function from sl classes to Pineapple classes.
Pineapple::InitParameters StereolabsToPine(
    const sl::InitParameters& initParameters);
Pineapple::RecordingParameters StereolabsToPine(
    const sl::RecordingParameters& recordingParameters);
Pineapple::RuntimeParameters StereolabsToPine(
    const sl::RuntimeParameters& runtimeParameters);
