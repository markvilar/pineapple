#include "Pineapple/Conversion.hpp"

sl::VIEW PineToStereolabs(const Pineapple::View& view)
{
    switch (view)
    {
    case Pineapple::View::Left:
        return sl::VIEW::LEFT;
    case Pineapple::View::Right:
        return sl::VIEW::RIGHT;
    case Pineapple::View::LeftGray:
        return sl::VIEW::LEFT_GRAY;
    case Pineapple::View::RightGray:
        return sl::VIEW::RIGHT_GRAY;
    case Pineapple::View::LeftUnrectified:
        return sl::VIEW::LEFT_UNRECTIFIED;
    case Pineapple::View::RightUnrectified:
        return sl::VIEW::RIGHT_UNRECTIFIED;
    case Pineapple::View::LeftUnrectifiedGray:
        return sl::VIEW::LEFT_UNRECTIFIED_GRAY;
    case Pineapple::View::RightUnrectifiedGray:
        return sl::VIEW::RIGHT_UNRECTIFIED_GRAY;
    case Pineapple::View::SideBySide:
        return sl::VIEW::SIDE_BY_SIDE;
    default:
        return sl::VIEW::LAST;
    }
}

sl::RESOLUTION PineToStereolabs(const Pineapple::Resolution& resolution)
{
    switch (resolution)
    {
    case Pineapple::Resolution::HD2K:
        return sl::RESOLUTION::HD2K;
    case Pineapple::Resolution::HD1080:
        return sl::RESOLUTION::HD1080;
    case Pineapple::Resolution::HD720:
        return sl::RESOLUTION::HD720;
    case Pineapple::Resolution::VGA:
        return sl::RESOLUTION::VGA;
    default:
        return sl::RESOLUTION::LAST;
    }
}

sl::VIDEO_SETTINGS PineToStereolabs(
    const Pineapple::VideoSettings& videoSettings)
{
    switch (videoSettings)
    {
    case Pineapple::VideoSettings::Brightness:
        return sl::VIDEO_SETTINGS::BRIGHTNESS;
    case Pineapple::VideoSettings::Contrast:
        return sl::VIDEO_SETTINGS::CONTRAST;
    case Pineapple::VideoSettings::Hue:
        return sl::VIDEO_SETTINGS::HUE;
    case Pineapple::VideoSettings::Saturation:
        return sl::VIDEO_SETTINGS::SATURATION;
    case Pineapple::VideoSettings::Sharpness:
        return sl::VIDEO_SETTINGS::SHARPNESS;
    case Pineapple::VideoSettings::Gain:
        return sl::VIDEO_SETTINGS::GAIN;
    case Pineapple::VideoSettings::Exposure:
        return sl::VIDEO_SETTINGS::EXPOSURE;
    case Pineapple::VideoSettings::AECAGC:
        return sl::VIDEO_SETTINGS::AEC_AGC;
    case Pineapple::VideoSettings::WhitebalanceTemperature:
        return sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE;
    case Pineapple::VideoSettings::WhitebalanceAuto:
        return sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO;
    case Pineapple::VideoSettings::LEDStatus:
        return sl::VIDEO_SETTINGS::LED_STATUS;
    default:
        return sl::VIDEO_SETTINGS::LAST;
    }
}

sl::DEPTH_MODE PineToStereolabs(const Pineapple::DepthMode& depthMode)
{
    switch (depthMode)
    {
    case Pineapple::DepthMode::Performance:
        return sl::DEPTH_MODE::PERFORMANCE;
    case Pineapple::DepthMode::Quality:
        return sl::DEPTH_MODE::QUALITY;
    case Pineapple::DepthMode::Ultra:
        return sl::DEPTH_MODE::ULTRA;
    default:
        return sl::DEPTH_MODE::LAST;
    }
}

sl::FLIP_MODE PineToStereolabs(const Pineapple::FlipMode& flipMode)
{
    switch (flipMode)
    {
    case Pineapple::FlipMode::Off:
        return sl::FLIP_MODE::OFF;
    case Pineapple::FlipMode::On:
        return sl::FLIP_MODE::ON;
    case Pineapple::FlipMode::Auto:
        return sl::FLIP_MODE::AUTO;
    default:
        return sl::FLIP_MODE::OFF;
    }
}

sl::UNIT PineToStereolabs(const Pineapple::Unit& unit)
{
    switch (unit)
    {
    case Pineapple::Unit::Millimeter:
        return sl::UNIT::MILLIMETER;
    case Pineapple::Unit::Centimeter:
        return sl::UNIT::CENTIMETER;
    case Pineapple::Unit::Meter:
        return sl::UNIT::METER;
    case Pineapple::Unit::Inch:
        return sl::UNIT::INCH;
    case Pineapple::Unit::Foot:
        return sl::UNIT::FOOT;
    default:
        return sl::UNIT::LAST;
    }
}

sl::SVO_COMPRESSION_MODE PineToStereolabs(
    const Pineapple::SVOCompressionMode& compressionMode)
{
    switch (compressionMode)
    {
    case Pineapple::SVOCompressionMode::Lossless:
        return sl::SVO_COMPRESSION_MODE::LOSSLESS;
    case Pineapple::SVOCompressionMode::H264:
        return sl::SVO_COMPRESSION_MODE::H264;
    case Pineapple::SVOCompressionMode::H265:
        return sl::SVO_COMPRESSION_MODE::H265;
    default:
        return sl::SVO_COMPRESSION_MODE::LAST;
    }
}

sl::SENSING_MODE PineToStereolabs(const Pineapple::SensingMode& sensingMode)
{
    switch (sensingMode)
    {
    case Pineapple::SensingMode::Standard:
        return sl::SENSING_MODE::STANDARD;
    case Pineapple::SensingMode::Fill:
        return sl::SENSING_MODE::FILL;
    default:
        return sl::SENSING_MODE::LAST;
    }
}

sl::REFERENCE_FRAME PineToStereolabs(
    const Pineapple::ReferenceFrame& referenceFrame)
{
    switch (referenceFrame)
    {
    case Pineapple::ReferenceFrame::World:
        return sl::REFERENCE_FRAME::WORLD;
    case Pineapple::ReferenceFrame::Camera:
        return sl::REFERENCE_FRAME::CAMERA;
    default:
        return sl::REFERENCE_FRAME::LAST;
    }
}

sl::COORDINATE_SYSTEM PineToStereolabs(
    const Pineapple::CoordinateSystem& coordinateSystem)
{
    switch (coordinateSystem)
    {
    case Pineapple::CoordinateSystem::Image:
        return sl::COORDINATE_SYSTEM::IMAGE;
    case Pineapple::CoordinateSystem::LeftHandedYUp:
        return sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP;
    case Pineapple::CoordinateSystem::RightHandedYUp:
        return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
    case Pineapple::CoordinateSystem::RightHandedZUp:
        return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP;
    case Pineapple::CoordinateSystem::LeftHandedZUp:
        return sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP;
    case Pineapple::CoordinateSystem::RightHandedZUpXForward:
        return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD;
    default:
        return sl::COORDINATE_SYSTEM::LAST;
    }
}

sl::InitParameters PineToStereolabs(
    const Pineapple::InitParameters& initParameters)
{
    sl::InitParameters params;
    params.depth_mode = PineToStereolabs(initParameters.depthMode);
    params.coordinate_units = PineToStereolabs(initParameters.coordinateUnits);

    params.coordinate_system =
        PineToStereolabs(initParameters.coordinateSystem);
    params.depth_stabilization = (int)initParameters.enableDepthStabilization;
    params.depth_minimum_distance = initParameters.minDepth;
    params.depth_maximum_distance = initParameters.maxDepth;
    params.enable_right_side_measure = initParameters.enableRightSideDepth;

    params.camera_resolution = PineToStereolabs(initParameters.resolution);
    params.camera_image_flip = PineToStereolabs(initParameters.flipMode);
    params.camera_fps = initParameters.cameraFPS;
    params.enable_image_enhancement = initParameters.enableImageEnhancement;
    params.camera_disable_self_calib = initParameters.disableSelfCalibration;
    params.sdk_verbose = initParameters.enableVerboseSDK;
    params.sensors_required = initParameters.requireSensors;
    return params;
}

sl::RecordingParameters PineToStereolabs(
    const Pineapple::RecordingParameters& recordingParameters)
{
    sl::RecordingParameters params;
    params.video_filename = sl::String(recordingParameters.filename.c_str());
    params.compression_mode =
        PineToStereolabs(recordingParameters.compressionMode);
    return params;
}

sl::RuntimeParameters PineToStereolabs(
    const Pineapple::RuntimeParameters& runtimeParameters)
{
    sl::RuntimeParameters params;
    params.sensing_mode = PineToStereolabs(runtimeParameters.sensingMode);
    params.measure3D_reference_frame =
        PineToStereolabs(runtimeParameters.referenceFrame);
    params.enable_depth = runtimeParameters.enableDepth;
    params.confidence_threshold = runtimeParameters.confidenceThreshold;
    params.texture_confidence_threshold =
        runtimeParameters.textureConfidenceThreshold;
    return params;
}

///////////////////////////////////////////////////////////////////////////////
// Pine conversion functions ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Pineapple::View StereolabsToPine(const sl::VIEW& view)
{
    switch (view)
    {
    case sl::VIEW::LEFT:
        return Pineapple::View::Left;
    case sl::VIEW::RIGHT:
        return Pineapple::View::Right;
    case sl::VIEW::LEFT_GRAY:
        return Pineapple::View::LeftGray;
    case sl::VIEW::RIGHT_GRAY:
        return Pineapple::View::RightGray;
    case sl::VIEW::LEFT_UNRECTIFIED:
        return Pineapple::View::LeftUnrectified;
    case sl::VIEW::RIGHT_UNRECTIFIED:
        return Pineapple::View::RightUnrectified;
    case sl::VIEW::LEFT_UNRECTIFIED_GRAY:
        return Pineapple::View::LeftUnrectifiedGray;
    case sl::VIEW::RIGHT_UNRECTIFIED_GRAY:
        return Pineapple::View::RightUnrectifiedGray;
    case sl::VIEW::SIDE_BY_SIDE:
        return Pineapple::View::SideBySide;
    default:
        return Pineapple::View::None;
    }
}

Pineapple::Resolution StereolabsToPine(const sl::RESOLUTION& resolution)
{
    switch (resolution)
    {
    case sl::RESOLUTION::HD2K:
        return Pineapple::Resolution::HD2K;
    case sl::RESOLUTION::HD1080:
        return Pineapple::Resolution::HD1080;
    case sl::RESOLUTION::HD720:
        return Pineapple::Resolution::HD720;
    case sl::RESOLUTION::VGA:
        return Pineapple::Resolution::VGA;
    default:
        return Pineapple::Resolution::None;
    }
}

Pineapple::VideoSettings StereolabsToPine(
    const sl::VIDEO_SETTINGS& videoSettings)
{
    switch (videoSettings)
    {
    case sl::VIDEO_SETTINGS::BRIGHTNESS:
        return Pineapple::VideoSettings::Brightness;
    case sl::VIDEO_SETTINGS::CONTRAST:
        return Pineapple::VideoSettings::Contrast;
    case sl::VIDEO_SETTINGS::HUE:
        return Pineapple::VideoSettings::Hue;
    case sl::VIDEO_SETTINGS::SATURATION:
        return Pineapple::VideoSettings::Saturation;
    case sl::VIDEO_SETTINGS::SHARPNESS:
        return Pineapple::VideoSettings::Sharpness;
    case sl::VIDEO_SETTINGS::GAIN:
        return Pineapple::VideoSettings::Gain;
    case sl::VIDEO_SETTINGS::EXPOSURE:
        return Pineapple::VideoSettings::Exposure;
    case sl::VIDEO_SETTINGS::AEC_AGC:
        return Pineapple::VideoSettings::AECAGC;
    case sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE:
        return Pineapple::VideoSettings::WhitebalanceTemperature;
    case sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO:
        return Pineapple::VideoSettings::WhitebalanceAuto;
    case sl::VIDEO_SETTINGS::LED_STATUS:
        return Pineapple::VideoSettings::LEDStatus;
    default:
        return Pineapple::VideoSettings::None;
    }
}

Pineapple::DepthMode StereolabsToPine(const sl::DEPTH_MODE& depthMode)
{
    switch (depthMode)
    {
    case sl::DEPTH_MODE::PERFORMANCE:
        return Pineapple::DepthMode::Performance;
    case sl::DEPTH_MODE::QUALITY:
        return Pineapple::DepthMode::Quality;
    case sl::DEPTH_MODE::ULTRA:
        return Pineapple::DepthMode::Ultra;
    default:
        return Pineapple::DepthMode::None;
    }
}

Pineapple::FlipMode StereolabsToPine(const int flipMode)
{
    switch (flipMode)
    {
    case sl::FLIP_MODE::OFF:
        return Pineapple::FlipMode::Off;
    case sl::FLIP_MODE::ON:
        return Pineapple::FlipMode::On;
    case sl::FLIP_MODE::AUTO:
        return Pineapple::FlipMode::Auto;
    default:
        return Pineapple::FlipMode::None;
    }
}

Pineapple::Unit StereolabsToPine(const sl::UNIT& unit)
{
    switch (unit)
    {
    case sl::UNIT::MILLIMETER:
        return Pineapple::Unit::Millimeter;
    case sl::UNIT::CENTIMETER:
        return Pineapple::Unit::Centimeter;
    case sl::UNIT::METER:
        return Pineapple::Unit::Meter;
    case sl::UNIT::INCH:
        return Pineapple::Unit::Inch;
    case sl::UNIT::FOOT:
        return Pineapple::Unit::Foot;
    default:
        return Pineapple::Unit::None;
    }
}

Pineapple::SVOCompressionMode StereolabsToPine(
    const sl::SVO_COMPRESSION_MODE& compressionMode)
{
    switch (compressionMode)
    {
    case sl::SVO_COMPRESSION_MODE::LOSSLESS:
        return Pineapple::SVOCompressionMode::Lossless;
    case sl::SVO_COMPRESSION_MODE::H264:
        return Pineapple::SVOCompressionMode::H264;
    case sl::SVO_COMPRESSION_MODE::H265:
        return Pineapple::SVOCompressionMode::H265;
    default:
        return Pineapple::SVOCompressionMode::None;
    }
}

Pineapple::SensingMode StereolabsToPine(const sl::SENSING_MODE& sensingMode)
{
    switch (sensingMode)
    {
    case sl::SENSING_MODE::STANDARD:
        return Pineapple::SensingMode::Standard;
    case sl::SENSING_MODE::FILL:
        return Pineapple::SensingMode::Fill;
    default:
        return Pineapple::SensingMode::None;
    }
}

Pineapple::ReferenceFrame StereolabsToPine(
    const sl::REFERENCE_FRAME& referenceFrame)
{
    switch (referenceFrame)
    {
    case sl::REFERENCE_FRAME::WORLD:
        return Pineapple::ReferenceFrame::World;
    case sl::REFERENCE_FRAME::CAMERA:
        return Pineapple::ReferenceFrame::Camera;
    default:
        return Pineapple::ReferenceFrame::None;
    }
}

Pineapple::CoordinateSystem StereolabsToPine(
    const sl::COORDINATE_SYSTEM& coordinateSystem)
{
    typedef Pineapple::CoordinateSystem CoordinateSystem;
    switch (coordinateSystem)
    {
    case sl::COORDINATE_SYSTEM::IMAGE:
        return CoordinateSystem::Image;
    case sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP:
        return CoordinateSystem::LeftHandedYUp;
    case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP:
        return CoordinateSystem::RightHandedYUp;
    case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP:
        return CoordinateSystem::RightHandedZUp;
    case sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP:
        return CoordinateSystem::LeftHandedZUp;
    case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD:
        return CoordinateSystem::RightHandedZUpXForward;
    default:
        return CoordinateSystem::None;
    }
}

Pineapple::InitParameters StereolabsToPine(
    const sl::InitParameters& initParameters)
{
    Pineapple::InitParameters params;
    params.depthMode = StereolabsToPine(initParameters.depth_mode);
    params.coordinateUnits = StereolabsToPine(initParameters.coordinate_units);
    params.coordinateSystem =
        StereolabsToPine(initParameters.coordinate_system);
    params.enableDepthStabilization = (bool)initParameters.depth_stabilization;
    params.minDepth = initParameters.depth_minimum_distance;
    params.maxDepth = initParameters.depth_maximum_distance;
    params.enableRightSideDepth = initParameters.enable_right_side_measure;

    params.resolution = StereolabsToPine(initParameters.camera_resolution);
    params.flipMode = StereolabsToPine(initParameters.camera_image_flip);
    params.cameraFPS = initParameters.camera_fps;
    params.enableImageEnhancement = initParameters.enable_image_enhancement;
    params.disableSelfCalibration = initParameters.camera_disable_self_calib;
    params.enableVerboseSDK = initParameters.sdk_verbose;
    params.requireSensors = initParameters.sensors_required;
    return params;
}

Pineapple::RecordingParameters StereolabsToPine(
    const sl::RecordingParameters& recordingParameters)
{
    Pineapple::RecordingParameters params;
    params.filename = std::string(recordingParameters.video_filename.get());
    params.compressionMode =
        StereolabsToPine(recordingParameters.compression_mode);
    return params;
}

Pineapple::RuntimeParameters StereolabsToPine(
    const sl::RuntimeParameters& runtimeParameters)
{
    Pineapple::RuntimeParameters params;
    params.sensingMode = StereolabsToPine(runtimeParameters.sensing_mode);
    params.referenceFrame =
        StereolabsToPine(runtimeParameters.measure3D_reference_frame);
    params.enableDepth = runtimeParameters.enable_depth;
    params.confidenceThreshold = runtimeParameters.confidence_threshold;
    params.textureConfidenceThreshold =
        runtimeParameters.texture_confidence_threshold;
    return params;
}
