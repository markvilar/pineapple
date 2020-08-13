#include <SennetZED/Primitives/Conversion.hpp>

sl::VIEW SennetToStereolabs(const Sennet::ZED::View& view)
{
	switch (view)
	{
		case Sennet::ZED::View::Left:
			return sl::VIEW::LEFT;
		case Sennet::ZED::View::Right:
			return sl::VIEW::RIGHT;
		case Sennet::ZED::View::LeftGray:
			return sl::VIEW::LEFT_GRAY;
		case Sennet::ZED::View::RightGray:
			return sl::VIEW::RIGHT_GRAY;
		case Sennet::ZED::View::LeftUnrectified:
			return sl::VIEW::LEFT_UNRECTIFIED;
		case Sennet::ZED::View::RightUnrectified:
			return sl::VIEW::RIGHT_UNRECTIFIED;
		case Sennet::ZED::View::LeftUnrectifiedGray:
			return sl::VIEW::LEFT_UNRECTIFIED_GRAY;
		case Sennet::ZED::View::RightUnrectifiedGray:
			return sl::VIEW::RIGHT_UNRECTIFIED_GRAY;
		case Sennet::ZED::View::SideBySide:
			return sl::VIEW::SIDE_BY_SIDE;
		default:
			return sl::VIEW::LAST;
	}
}

sl::RESOLUTION SennetToStereolabs(const Sennet::ZED::Resolution& resolution)
{
	switch (resolution)
	{
		case Sennet::ZED::Resolution::HD2K:
			return sl::RESOLUTION::HD2K;
		case Sennet::ZED::Resolution::HD1080:
			return sl::RESOLUTION::HD1080;
		case Sennet::ZED::Resolution::HD720:
			return sl::RESOLUTION::HD720;
		case Sennet::ZED::Resolution::VGA:
			return sl::RESOLUTION::VGA;
		default:
			return sl::RESOLUTION::LAST;
	}
}

sl::VIDEO_SETTINGS SennetToStereolabs(
	const Sennet::ZED::VideoSettings& videoSettings)
{
	switch (videoSettings)
	{
		case Sennet::ZED::VideoSettings::Brightness:
			return sl::VIDEO_SETTINGS::BRIGHTNESS;
		case Sennet::ZED::VideoSettings::Contrast:
			return sl::VIDEO_SETTINGS::CONTRAST;
		case Sennet::ZED::VideoSettings::Hue:
			return sl::VIDEO_SETTINGS::HUE;
		case Sennet::ZED::VideoSettings::Saturation:
			return sl::VIDEO_SETTINGS::SATURATION;
		case Sennet::ZED::VideoSettings::Sharpness:
			return sl::VIDEO_SETTINGS::SHARPNESS;
		case Sennet::ZED::VideoSettings::Gain:
			return sl::VIDEO_SETTINGS::GAIN;
		case Sennet::ZED::VideoSettings::Exposure:
			return sl::VIDEO_SETTINGS::EXPOSURE;
		case Sennet::ZED::VideoSettings::AECAGC:
			return sl::VIDEO_SETTINGS::AEC_AGC;
		case Sennet::ZED::VideoSettings::WhitebalanceTemperature:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE;
		case Sennet::ZED::VideoSettings::WhitebalanceAuto:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO;
		case Sennet::ZED::VideoSettings::LEDStatus:
			return sl::VIDEO_SETTINGS::LED_STATUS;
		default:
			return sl::VIDEO_SETTINGS::LAST;
	}
}

sl::DEPTH_MODE SennetToStereolabs(const Sennet::ZED::DepthMode& depthMode)
{
	switch (depthMode)
	{
		case Sennet::ZED::DepthMode::Performance:
			return sl::DEPTH_MODE::PERFORMANCE;
		case Sennet::ZED::DepthMode::Quality:
			return sl::DEPTH_MODE::QUALITY;
		case Sennet::ZED::DepthMode::Ultra:
			return sl::DEPTH_MODE::ULTRA;
		default:
			return sl::DEPTH_MODE::LAST;
	}
}

sl::UNIT SennetToStereolabs(const Sennet::ZED::Unit& unit)
{
	switch (unit)
	{
		case Sennet::ZED::Unit::Millimeter:
			return sl::UNIT::MILLIMETER;
		case Sennet::ZED::Unit::Centimeter:
			return sl::UNIT::CENTIMETER;
		case Sennet::ZED::Unit::Meter:
			return sl::UNIT::METER;
		case Sennet::ZED::Unit::Inch:
			return sl::UNIT::INCH;
		case Sennet::ZED::Unit::Foot:
			return sl::UNIT::FOOT;
		default:
			return sl::UNIT::LAST;
	}
}

sl::SVO_COMPRESSION_MODE SennetToStereolabs(
	const Sennet::ZED::SVOCompressionMode& compressionMode)
{
	switch (compressionMode)
	{
		case Sennet::ZED::SVOCompressionMode::Lossless:
			return sl::SVO_COMPRESSION_MODE::LOSSLESS;
		case Sennet::ZED::SVOCompressionMode::H264:
			return sl::SVO_COMPRESSION_MODE::H264;
		case Sennet::ZED::SVOCompressionMode::H265:
			return sl::SVO_COMPRESSION_MODE::H265;
		default:
			return sl::SVO_COMPRESSION_MODE::LAST;
	}
}

sl::SENSING_MODE SennetToStereolabs(const Sennet::ZED::SensingMode& sensingMode)
{
	switch (sensingMode)
	{
		case Sennet::ZED::SensingMode::Standard:
			return sl::SENSING_MODE::STANDARD;
		case Sennet::ZED::SensingMode::Fill:
			return sl::SENSING_MODE::FILL;
		default:
			return sl::SENSING_MODE::LAST;
	}
}

sl::REFERENCE_FRAME SennetToStereolabs(
	const Sennet::ZED::ReferenceFrame& referenceFrame)
{
	switch (referenceFrame)
	{
		case Sennet::ZED::ReferenceFrame::World: 
			return sl::REFERENCE_FRAME::WORLD;
		case Sennet::ZED::ReferenceFrame::Camera: 
			return sl::REFERENCE_FRAME::CAMERA;
		default: 
			return sl::REFERENCE_FRAME::LAST;
	}
}

sl::COORDINATE_SYSTEM SennetToStereolabs(
	const Sennet::ZED::CoordinateSystem& coordinateSystem)
{
	switch (coordinateSystem)
	{
		case Sennet::ZED::CoordinateSystem::Image:
			return sl::COORDINATE_SYSTEM::IMAGE;
		case Sennet::ZED::CoordinateSystem::LeftHandedYUp:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP;
		case Sennet::ZED::CoordinateSystem::RightHandedYUp:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
		case Sennet::ZED::CoordinateSystem::RightHandedZUp:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP;
		case Sennet::ZED::CoordinateSystem::LeftHandedZUp:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP;
		case Sennet::ZED::CoordinateSystem::RightHandedZUpXForward:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD;
		default:
			return sl::COORDINATE_SYSTEM::LAST;
	}
}

Sennet::Ref<sl::Mat> SennetToStereolabs(const Sennet::Ref<Sennet::Image>& image)
{
	auto mat_type = sl::MAT_TYPE::U8_C1;
	switch (image->GetChannels())
	{
		case 1:
			mat_type = sl::MAT_TYPE::U8_C1;
			break;
		case 2:
			mat_type = sl::MAT_TYPE::U8_C2;
			break;
		case 3:
			mat_type = sl::MAT_TYPE::U8_C3;
			break;
		case 4:
			mat_type = sl::MAT_TYPE::U8_C4;
			break;
		default:
			return nullptr;
	}
	return Sennet::CreateRef<sl::Mat>(image->GetWidth(), 
		image->GetHeight(), mat_type, (sl::uchar1*)image->GetPtr(),
		image->GetChannels());
}

sl::InitParameters SennetToStereolabs(
	const Sennet::ZED::InitParameters& initParameters)
{
	auto data = initParameters.GetData();
	sl::InitParameters slInitParameters;
	slInitParameters.depth_mode = SennetToStereolabs(data.depthMode);
	slInitParameters.coordinate_units = 
		SennetToStereolabs(data.coordinateUnits);
	slInitParameters.coordinate_system = 
		SennetToStereolabs(data.coordinateSystem);
	slInitParameters.depth_stabilization = data.depthStabilization;
	slInitParameters.depth_minimum_distance = data.minDepth;
	slInitParameters.depth_maximum_distance = data.maxDepth;
	slInitParameters.enable_right_side_measure = data.enableRightSideDepth;

	slInitParameters.camera_resolution = SennetToStereolabs(data.resolution);
	slInitParameters.camera_fps = data.cameraFPS;
	slInitParameters.enable_image_enhancement = data.enableImageEnhancement;
	slInitParameters.camera_disable_self_calib = data.disableSelfCalibration;
	slInitParameters.sdk_verbose = data.enableVerboseSDK;
	slInitParameters.sensors_required = data.requireSensors;
	return slInitParameters;
}

sl::RecordingParameters SennetToStereolabs(
	const Sennet::ZED::RecordingParameters& recordingParameters)
{
	auto data = recordingParameters.GetData();
	sl::RecordingParameters slRecordingParameters;
	slRecordingParameters.video_filename = sl::String(data.filename.c_str());
	slRecordingParameters.compression_mode = 
		SennetToStereolabs(data.compressionMode);
	return slRecordingParameters;
}

sl::RuntimeParameters SennetToStereolabs(
	const Sennet::ZED::RuntimeParameters& runtimeParameters)
{
	auto data = runtimeParameters.GetData();
	sl::RuntimeParameters slRuntimeParameters;
	slRuntimeParameters.sensing_mode = SennetToStereolabs(data.sensingMode);
	slRuntimeParameters.measure3D_reference_frame = 
		SennetToStereolabs(data.referenceFrame);
	slRuntimeParameters.enable_depth = data.enableDepth;
	slRuntimeParameters.confidence_threshold = data.confidenceThreshold;
	slRuntimeParameters.textureness_confidence_threshold 
		= data.textureConfidenceThreshold;
	return slRuntimeParameters;
}

///////////////////////////////////////////////////////////////////////////////
// Sennet conversion functions ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Sennet::ZED::View StereolabsToSennet(const sl::VIEW& view)
{
	switch (view)
	{
		case sl::VIEW::LEFT:
			return Sennet::ZED::View::Left;
		case sl::VIEW::RIGHT:
			return Sennet::ZED::View::Right;
		case sl::VIEW::LEFT_GRAY:
			return Sennet::ZED::View::LeftGray;
		case sl::VIEW::RIGHT_GRAY:
			return Sennet::ZED::View::RightGray;
		case sl::VIEW::LEFT_UNRECTIFIED:
			return Sennet::ZED::View::LeftUnrectified;
		case sl::VIEW::RIGHT_UNRECTIFIED:
			return Sennet::ZED::View::RightUnrectified;
		case sl::VIEW::LEFT_UNRECTIFIED_GRAY:
			return Sennet::ZED::View::LeftUnrectifiedGray;
		case sl::VIEW::RIGHT_UNRECTIFIED_GRAY:
			return Sennet::ZED::View::RightUnrectifiedGray;
		case sl::VIEW::SIDE_BY_SIDE:
			return Sennet::ZED::View::SideBySide;
		default:
			return Sennet::ZED::View::None;
	}
}

Sennet::ZED::Resolution StereolabsToSennet(const sl::RESOLUTION& resolution)
{
	switch (resolution)
	{
		case sl::RESOLUTION::HD2K:
			return Sennet::ZED::Resolution::HD2K;
		case sl::RESOLUTION::HD1080:
			return Sennet::ZED::Resolution::HD1080;
		case sl::RESOLUTION::HD720:
			return Sennet::ZED::Resolution::HD720;
		case sl::RESOLUTION::VGA:
			return Sennet::ZED::Resolution::VGA;
		default:
			return Sennet::ZED::Resolution::None;
	}
}

Sennet::ZED::VideoSettings StereolabsToSennet(
	const sl::VIDEO_SETTINGS& videoSettings)
{
	switch (videoSettings)
	{
		case sl::VIDEO_SETTINGS::BRIGHTNESS:
			return Sennet::ZED::VideoSettings::Brightness;
		case sl::VIDEO_SETTINGS::CONTRAST:
			return Sennet::ZED::VideoSettings::Contrast;
		case sl::VIDEO_SETTINGS::HUE:
			return Sennet::ZED::VideoSettings::Hue;
		case sl::VIDEO_SETTINGS::SATURATION:
			return Sennet::ZED::VideoSettings::Saturation;
		case sl::VIDEO_SETTINGS::SHARPNESS:
			return Sennet::ZED::VideoSettings::Sharpness;
		case sl::VIDEO_SETTINGS::GAIN:
			return Sennet::ZED::VideoSettings::Gain;
		case sl::VIDEO_SETTINGS::EXPOSURE:
			return Sennet::ZED::VideoSettings::Exposure;
		case sl::VIDEO_SETTINGS::AEC_AGC:
			return Sennet::ZED::VideoSettings::AECAGC;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE:
			return Sennet::ZED::VideoSettings::WhitebalanceTemperature;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO:
			return Sennet::ZED::VideoSettings::WhitebalanceAuto;
		case sl::VIDEO_SETTINGS::LED_STATUS:
			return Sennet::ZED::VideoSettings::LEDStatus;
		default:
			return Sennet::ZED::VideoSettings::None;
	}
}

Sennet::ZED::DepthMode StereolabsToSennet(const sl::DEPTH_MODE& depthMode)
{
	switch (depthMode)
	{
		case sl::DEPTH_MODE::PERFORMANCE:
			return Sennet::ZED::DepthMode::Performance;
		case sl::DEPTH_MODE::QUALITY:
			return Sennet::ZED::DepthMode::Quality;
		case sl::DEPTH_MODE::ULTRA:
			return Sennet::ZED::DepthMode::Ultra;
		default:
			return Sennet::ZED::DepthMode::None;
	}
}

Sennet::ZED::Unit StereolabsToSennet(const sl::UNIT& unit)
{
	switch (unit)
	{
		case sl::UNIT::MILLIMETER:
			return Sennet::ZED::Unit::Millimeter;		
		case sl::UNIT::CENTIMETER:
			return Sennet::ZED::Unit::Centimeter;
		case sl::UNIT::METER:
			return Sennet::ZED::Unit::Meter;
		case sl::UNIT::INCH:
			return Sennet::ZED::Unit::Inch;
		case sl::UNIT::FOOT:
			return Sennet::ZED::Unit::Foot;
		default:
			return Sennet::ZED::Unit::None;
	}
}

Sennet::ZED::SVOCompressionMode StereolabsToSennet(
	const sl::SVO_COMPRESSION_MODE& compressionMode)
{
	switch (compressionMode)
	{
		case sl::SVO_COMPRESSION_MODE::LOSSLESS:
			return Sennet::ZED::SVOCompressionMode::Lossless;
		case sl::SVO_COMPRESSION_MODE::H264:
			return Sennet::ZED::SVOCompressionMode::H264;
		case sl::SVO_COMPRESSION_MODE::H265:
			return Sennet::ZED::SVOCompressionMode::H265;
		default:
			return Sennet::ZED::SVOCompressionMode::None;
	}
}

Sennet::ZED::SensingMode StereolabsToSennet(const sl::SENSING_MODE& sensingMode)
{
	switch (sensingMode)
	{
		case sl::SENSING_MODE::STANDARD:
			return Sennet::ZED::SensingMode::Standard;
		case sl::SENSING_MODE::FILL:
			return Sennet::ZED::SensingMode::Fill;
		default:
			return Sennet::ZED::SensingMode::None;
	}
}

Sennet::ZED::ReferenceFrame StereolabsToSennet(
	const sl::REFERENCE_FRAME& referenceFrame)
{
	switch (referenceFrame)
	{
		case sl::REFERENCE_FRAME::WORLD:
			return Sennet::ZED::ReferenceFrame::World;		
		case sl::REFERENCE_FRAME::CAMERA:
			return Sennet::ZED::ReferenceFrame::Camera;
		default:
			return Sennet::ZED::ReferenceFrame::None;
	}
}

Sennet::ZED::CoordinateSystem StereolabsToSennet(
	const sl::COORDINATE_SYSTEM& coordinateSystem)
{
	typedef Sennet::ZED::CoordinateSystem CoordinateSystem;
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

Sennet::Ref<Sennet::Image> StereolabsToSennet(
	const Sennet::Ref<sl::Mat>& mat)
{
	return Sennet::CreateRef<Sennet::Image>(
		mat->getPtr<unsigned char>(), mat->getWidth(), 
		mat->getHeight(), mat->getChannels());
}

Sennet::ZED::InitParameters StereolabsToSennet(
	const sl::InitParameters& initParameters)
{
	Sennet::ZED::InitParametersData data;
	data.depthMode = StereolabsToSennet(initParameters.depth_mode);
	data.coordinateUnits = StereolabsToSennet(initParameters.coordinate_units);
	data.coordinateSystem = StereolabsToSennet(initParameters.coordinate_system);
	data.depthStabilization = initParameters.depth_stabilization;
	data.minDepth = initParameters.depth_minimum_distance;
	data.maxDepth = initParameters.depth_maximum_distance;
	data.enableRightSideDepth = initParameters.enable_right_side_measure;

	data.resolution = StereolabsToSennet(initParameters.camera_resolution);
	data.cameraFPS = initParameters.camera_fps;
	data.enableImageEnhancement = initParameters.enable_image_enhancement;
	data.disableSelfCalibration = initParameters.camera_disable_self_calib;
	data.enableVerboseSDK = initParameters.sdk_verbose;
	data.requireSensors = initParameters.sensors_required;
	return Sennet::ZED::InitParameters(data);
}

Sennet::ZED::RecordingParameters StereolabsToSennet(
	const sl::RecordingParameters& recordingParameters)
{
	Sennet::ZED::RecordingParametersData data;
	data.filename = std::string(recordingParameters.video_filename.get());
	data.compressionMode = 
		StereolabsToSennet(recordingParameters.compression_mode);
	return Sennet::ZED::RecordingParameters(data);
}

Sennet::ZED::RuntimeParameters StereolabsToSennet(
	const sl::RuntimeParameters& runtimeParameters)
{
	Sennet::ZED::RuntimeParametersData data;
	data.sensingMode = StereolabsToSennet(runtimeParameters.sensing_mode);
	data.referenceFrame = 
		StereolabsToSennet(runtimeParameters.measure3D_reference_frame);
	data.enableDepth = runtimeParameters.enable_depth;
	data.confidenceThreshold = runtimeParameters.confidence_threshold;
	data.textureConfidenceThreshold = 
		runtimeParameters.textureness_confidence_threshold;
	return Sennet::ZED::RuntimeParameters(data);
}
