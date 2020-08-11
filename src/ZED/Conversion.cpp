#include <SennetZED/ZED/Conversion.hpp>

sl::VIEW SennetToStereolabs(const Sennet::ZED::view& sn_view)
{
	switch (sn_view)
	{
		case Sennet::ZED::view::left:
			return sl::VIEW::LEFT;
		case Sennet::ZED::view::right:
			return sl::VIEW::RIGHT;
		case Sennet::ZED::view::left_gray:
			return sl::VIEW::LEFT_GRAY;
		case Sennet::ZED::view::right_gray:
			return sl::VIEW::RIGHT_GRAY;
		case Sennet::ZED::view::left_unrectified:
			return sl::VIEW::LEFT_UNRECTIFIED;
		case Sennet::ZED::view::right_unrectified:
			return sl::VIEW::RIGHT_UNRECTIFIED;
		case Sennet::ZED::view::left_unrectified_gray:
			return sl::VIEW::LEFT_UNRECTIFIED_GRAY;
		case Sennet::ZED::view::right_unrectified_gray:
			return sl::VIEW::RIGHT_UNRECTIFIED_GRAY;
		case Sennet::ZED::view::side_by_side:
			return sl::VIEW::SIDE_BY_SIDE;
		default:
			return sl::VIEW::LAST;
	}
}

sl::RESOLUTION SennetToStereolabs(const Sennet::ZED::resolution& sn_res)
{
	switch (sn_res)
	{
		case Sennet::ZED::resolution::hd2k:
			return sl::RESOLUTION::HD2K;
		case Sennet::ZED::resolution::hd1080:
			return sl::RESOLUTION::HD1080;
		case Sennet::ZED::resolution::hd720:
			return sl::RESOLUTION::HD720;
		case Sennet::ZED::resolution::vga:
			return sl::RESOLUTION::VGA;
		default:
			return sl::RESOLUTION::LAST;
	}
}

sl::VIDEO_SETTINGS SennetToStereolabs(
	const Sennet::ZED::video_settings& sn_video)
{
	switch (sn_video)
	{
		case Sennet::ZED::video_settings::brightness:
			return sl::VIDEO_SETTINGS::BRIGHTNESS;
		case Sennet::ZED::video_settings::contrast:
			return sl::VIDEO_SETTINGS::CONTRAST;
		case Sennet::ZED::video_settings::hue:
			return sl::VIDEO_SETTINGS::HUE;
		case Sennet::ZED::video_settings::saturation:
			return sl::VIDEO_SETTINGS::SATURATION;
		case Sennet::ZED::video_settings::sharpness:
			return sl::VIDEO_SETTINGS::SHARPNESS;
		case Sennet::ZED::video_settings::gain:
			return sl::VIDEO_SETTINGS::GAIN;
		case Sennet::ZED::video_settings::exposure:
			return sl::VIDEO_SETTINGS::EXPOSURE;
		case Sennet::ZED::video_settings::aec_agc:
			return sl::VIDEO_SETTINGS::AEC_AGC;
		case Sennet::ZED::video_settings::whitebalance_temperature:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE;
		case Sennet::ZED::video_settings::whitebalance_auto:
			return sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO;
		case Sennet::ZED::video_settings::led_status:
			return sl::VIDEO_SETTINGS::LED_STATUS;
		default:
			return sl::VIDEO_SETTINGS::LAST;
	}
}

sl::DEPTH_MODE SennetToStereolabs(const Sennet::ZED::depth_mode& sn_depth)
{
	switch (sn_depth)
	{
		case Sennet::ZED::depth_mode::performance:
			return sl::DEPTH_MODE::PERFORMANCE;
		case Sennet::ZED::depth_mode::quality:
			return sl::DEPTH_MODE::QUALITY;
		case Sennet::ZED::depth_mode::ultra:
			return sl::DEPTH_MODE::ULTRA;
		default:
			return sl::DEPTH_MODE::LAST;
	}
}

sl::UNIT SennetToStereolabs(const Sennet::ZED::unit& sn_unit)
{
	switch (sn_unit)
	{
		case Sennet::ZED::unit::millimeter:
			return sl::UNIT::MILLIMETER;
		case Sennet::ZED::unit::centimeter:
			return sl::UNIT::CENTIMETER;
		case Sennet::ZED::unit::meter:
			return sl::UNIT::METER;
		case Sennet::ZED::unit::inch:
			return sl::UNIT::INCH;
		case Sennet::ZED::unit::foot:
			return sl::UNIT::FOOT;
		default:
			return sl::UNIT::LAST;
	}
}

sl::SVO_COMPRESSION_MODE SennetToStereolabs(
	const Sennet::ZED::svo_compression_mode& sn_compr)
{
	switch (sn_compr)
	{
		case Sennet::ZED::svo_compression_mode::lossless:
			return sl::SVO_COMPRESSION_MODE::LOSSLESS;
		case Sennet::ZED::svo_compression_mode::h264:
			return sl::SVO_COMPRESSION_MODE::H264;
		case Sennet::ZED::svo_compression_mode::h265:
			return sl::SVO_COMPRESSION_MODE::H265;
		default:
			return sl::SVO_COMPRESSION_MODE::LAST;
	}
}

sl::SENSING_MODE SennetToStereolabs(const Sennet::ZED::sensing_mode& sn_sensing)
{
	switch (sn_sensing)
	{
		case Sennet::ZED::sensing_mode::standard:
			return sl::SENSING_MODE::STANDARD;
		case Sennet::ZED::sensing_mode::fill:
			return sl::SENSING_MODE::FILL;
		default:
			return sl::SENSING_MODE::LAST;
	}
}

sl::REFERENCE_FRAME SennetToStereolabs(
	const Sennet::ZED::reference_frame& sn_ref)
{
	switch (sn_ref)
	{
		case Sennet::ZED::reference_frame::world: 
			return sl::REFERENCE_FRAME::WORLD;
		case Sennet::ZED::reference_frame::camera: 
			return sl::REFERENCE_FRAME::CAMERA;
		default: 
			return sl::REFERENCE_FRAME::LAST;
	}
}

sl::COORDINATE_SYSTEM SennetToStereolabs(
	const Sennet::ZED::coordinate_system& sn_sys)
{
	switch (sn_sys)
	{
		case Sennet::ZED::coordinate_system::image:
			return sl::COORDINATE_SYSTEM::IMAGE;
		case Sennet::ZED::coordinate_system::left_handed_y_up:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP;
		case Sennet::ZED::coordinate_system::right_handed_y_up:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
		case Sennet::ZED::coordinate_system::right_handed_z_up:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP;
		case Sennet::ZED::coordinate_system::left_handed_z_up:
			return sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP;
		case Sennet::ZED::coordinate_system::right_handed_z_up_x_fwd:
			return sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD;
		default:
			return sl::COORDINATE_SYSTEM::LAST;
	}
}

Sennet::Ref<sl::Mat> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::image> sn_img)
{
	auto mat_type = sl::MAT_TYPE::U8_C1;
	switch (sn_img->get_channels())
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
	return Sennet::CreateRef<sl::Mat>(sn_img->get_width(), 
		sn_img->get_height(), mat_type, (sl::uchar1*)sn_img->get_ptr(),
		sn_img->get_channels());
}

Sennet::Ref<sl::InitParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::init_params> sn_ip)
{
	auto sl_ip = Sennet::CreateRef<sl::InitParameters>();

	// Depth parameters.
	sl_ip->depth_mode = SennetToStereolabs(sn_ip->get_depth_mode());
	sl_ip->coordinate_units = SennetToStereolabs(sn_ip->get_coord_units());
	sl_ip->coordinate_system = SennetToStereolabs(sn_ip->get_coord_sys());
	sl_ip->depth_stabilization = sn_ip->get_depth_stab();
	sl_ip->depth_minimum_distance = sn_ip->get_min_depth();
	sl_ip->depth_maximum_distance = sn_ip->get_max_depth();
	sl_ip->enable_right_side_measure = sn_ip->right_depth_enabled();

	// Generic parameters.
	sl_ip->camera_resolution = ::SennetToStereolabs(sn_ip->get_resolution());
	sl_ip->camera_fps = sn_ip->get_camera_fps();
	sl_ip->enable_image_enhancement = sn_ip->img_enhance_enabled();
	sl_ip->camera_disable_self_calib = sn_ip->self_calib_disabled();
	sl_ip->sdk_verbose = sn_ip->is_sdk_verbose();
	sl_ip->sensors_required = sn_ip->sensors_required();

	return sl_ip;
}

Sennet::Ref<sl::RecordingParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::recording_params> sn_rp)
{
	auto sl_rp = Sennet::CreateRef<sl::RecordingParameters>();

	sl_rp->video_filename = sl::String(sn_rp->get_filename().c_str());
	sl_rp->compression_mode = SennetToStereolabs(sn_rp->get_compression_mode());

	return sl_rp;
}

Sennet::Ref<sl::RuntimeParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::runtime_params> sn_rp)
{
	auto sl_rp = Sennet::CreateRef<sl::RuntimeParameters>();
	sl_rp->sensing_mode = SennetToStereolabs(sn_rp->get_sensing_mode());
	sl_rp->measure3D_reference_frame = 
		SennetToStereolabs(sn_rp->get_reference_frame());
	sl_rp->enable_depth = sn_rp->is_depth_enabled();
	sl_rp->confidence_threshold = sn_rp->get_confidence_threshold();
	sl_rp->textureness_confidence_threshold =
		sn_rp->get_texture_confidence_threshold();
	return sl_rp;
}

///////////////////////////////////////////////////////////////////////////////
// Sennet conversion functions ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

Sennet::ZED::view StereolabsToSennet(const sl::VIEW& sl_view)
{
	typedef Sennet::ZED::view zed_view;
	switch (sl_view)
	{
		case sl::VIEW::LEFT:
			return zed_view::left;
		case sl::VIEW::RIGHT:
			return zed_view::right;
		case sl::VIEW::LEFT_GRAY:
			return zed_view::left_gray;
		case sl::VIEW::RIGHT_GRAY:
			return zed_view::right_gray;
		case sl::VIEW::LEFT_UNRECTIFIED:
			return zed_view::left_unrectified;
		case sl::VIEW::RIGHT_UNRECTIFIED:
			return zed_view::right_unrectified;
		case sl::VIEW::LEFT_UNRECTIFIED_GRAY:
			return zed_view::left_unrectified_gray;
		case sl::VIEW::RIGHT_UNRECTIFIED_GRAY:
			return zed_view::right_unrectified_gray;
		case sl::VIEW::SIDE_BY_SIDE:
			return zed_view::side_by_side;
		default:
			return zed_view::none;
	}
}

Sennet::ZED::resolution StereolabsToSennet(const sl::RESOLUTION& sl_res)
{
	typedef Sennet::ZED::resolution zed_resolution;
	switch (sl_res)
	{
		case sl::RESOLUTION::HD2K:
			return zed_resolution::hd2k;
		case sl::RESOLUTION::HD1080:
			return zed_resolution::hd1080;
		case sl::RESOLUTION::HD720:
			return zed_resolution::hd720;
		case sl::RESOLUTION::VGA:
			return zed_resolution::vga;
		default:
			return zed_resolution::none;
	}
}

Sennet::ZED::video_settings StereolabsToSennet(
	const sl::VIDEO_SETTINGS& sl_video)
{
	typedef Sennet::ZED::video_settings zed_video_settings;
	switch (sl_video)
	{
		case sl::VIDEO_SETTINGS::BRIGHTNESS:
			return zed_video_settings::brightness;
		case sl::VIDEO_SETTINGS::CONTRAST:
			return zed_video_settings::contrast;
		case sl::VIDEO_SETTINGS::HUE:
			return zed_video_settings::hue;
		case sl::VIDEO_SETTINGS::SATURATION:
			return zed_video_settings::saturation;
		case sl::VIDEO_SETTINGS::SHARPNESS:
			return zed_video_settings::sharpness;
		case sl::VIDEO_SETTINGS::GAIN:
			return zed_video_settings::gain;
		case sl::VIDEO_SETTINGS::EXPOSURE:
			return zed_video_settings::exposure;
		case sl::VIDEO_SETTINGS::AEC_AGC:
			return zed_video_settings::aec_agc;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE:
			return zed_video_settings::whitebalance_temperature;
		case sl::VIDEO_SETTINGS::WHITEBALANCE_AUTO:
			return zed_video_settings::whitebalance_auto;
		case sl::VIDEO_SETTINGS::LED_STATUS:
			return zed_video_settings::led_status;
		default:
			return zed_video_settings::none;
	}
}

Sennet::ZED::depth_mode StereolabsToSennet(const sl::DEPTH_MODE& sl_depth)
{
	typedef Sennet::ZED::depth_mode zed_depth_mode;
	switch (sl_depth)
	{
		case sl::DEPTH_MODE::PERFORMANCE:
			return zed_depth_mode::performance;
		case sl::DEPTH_MODE::QUALITY:
			return zed_depth_mode::quality;
		case sl::DEPTH_MODE::ULTRA:
			return zed_depth_mode::ultra;
		default:
			return zed_depth_mode::none;
	}
}

Sennet::ZED::unit StereolabsToSennet(const sl::UNIT& sl_unit)
{
	typedef Sennet::ZED::unit zed_unit;
	switch (sl_unit)
	{
		case sl::UNIT::MILLIMETER:
			return zed_unit::millimeter;		
		case sl::UNIT::CENTIMETER:
			return zed_unit::centimeter;
		case sl::UNIT::METER:
			return zed_unit::meter;
		case sl::UNIT::INCH:
			return zed_unit::inch;
		case sl::UNIT::FOOT:
			return zed_unit::foot;
		default:
			return zed_unit::none;
	}
}

Sennet::ZED::svo_compression_mode StereolabsToSennet(
	const sl::SVO_COMPRESSION_MODE& sl_compr)
{
	typedef Sennet::ZED::svo_compression_mode zed_svo_compression_mode;
	switch (sl_compr)
	{
		case sl::SVO_COMPRESSION_MODE::LOSSLESS:
			return zed_svo_compression_mode::lossless;
		case sl::SVO_COMPRESSION_MODE::H264:
			return zed_svo_compression_mode::h264;
		case sl::SVO_COMPRESSION_MODE::H265:
			return zed_svo_compression_mode::h265;
		default:
			return zed_svo_compression_mode::none;
	}
}

Sennet::ZED::sensing_mode StereolabsToSennet(const sl::SENSING_MODE& sl_sensing)
{
	typedef Sennet::ZED::sensing_mode zed_sensing_mode;
	switch (sl_sensing)
	{
		case sl::SENSING_MODE::STANDARD:
			return zed_sensing_mode::standard;
		case sl::SENSING_MODE::FILL:
			return zed_sensing_mode::fill;
		default:
			return zed_sensing_mode::none;
	}
}

Sennet::ZED::reference_frame StereolabsToSennet(
	const sl::REFERENCE_FRAME& sl_ref)
{
	typedef Sennet::ZED::reference_frame zed_ref_frame;
	switch (sl_ref)
	{
		case sl::REFERENCE_FRAME::WORLD:
			return zed_ref_frame::world;		
		case sl::REFERENCE_FRAME::CAMERA:
			return zed_ref_frame::camera;
		default:
			return zed_ref_frame::none;
	}
}

Sennet::ZED::coordinate_system StereolabsToSennet(
	const sl::COORDINATE_SYSTEM& sl_sys)
{
	typedef Sennet::ZED::coordinate_system zed_coord_sys;
	switch (sl_sys)
	{
		case sl::COORDINATE_SYSTEM::IMAGE:
			return zed_coord_sys::image;
		case sl::COORDINATE_SYSTEM::LEFT_HANDED_Y_UP:
			return zed_coord_sys::left_handed_y_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP:
			return zed_coord_sys::right_handed_y_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP:
			return zed_coord_sys::right_handed_z_up;
		case sl::COORDINATE_SYSTEM::LEFT_HANDED_Z_UP:
			return zed_coord_sys::left_handed_z_up;
		case sl::COORDINATE_SYSTEM::RIGHT_HANDED_Z_UP_X_FWD:
			return zed_coord_sys::right_handed_z_up_x_fwd;
		default:
			return zed_coord_sys::none;
	}
}

Sennet::Ref<Sennet::ZED::image> StereolabsToSennet(
	const Sennet::Ref<sl::Mat> sl_img)
{
	switch (sl_img->getDataType())
	{
		case sl::MAT_TYPE::U8_C1:
			break;
		case sl::MAT_TYPE::U8_C2:
			break;
		case sl::MAT_TYPE::U8_C3:
			break;
		case sl::MAT_TYPE::U8_C4:
			break;
		default:
			return nullptr;
	}
	return Sennet::CreateRef<Sennet::ZED::image>(
		sl_img->getPtr<unsigned char>(), sl_img->getWidth(), 
		sl_img->getHeight(), sl_img->getChannels());
}

Sennet::Ref<Sennet::ZED::init_params> StereolabsToSennet(
	const Sennet::Ref<sl::InitParameters> sl_ip)
{
	return Sennet::CreateRef<Sennet::ZED::init_params>(
		StereolabsToSennet(sl_ip->depth_mode),
		StereolabsToSennet(sl_ip->coordinate_units),
		StereolabsToSennet(sl_ip->coordinate_system),
		sl_ip->depth_stabilization,
		sl_ip->depth_minimum_distance,
		sl_ip->depth_maximum_distance,
		sl_ip->enable_right_side_measure,
		StereolabsToSennet(sl_ip->camera_resolution),
		sl_ip->camera_fps,
		sl_ip->enable_image_enhancement,
		sl_ip->camera_disable_self_calib,
		sl_ip->sdk_verbose,
		sl_ip->sensors_required);
}

Sennet::Ref<Sennet::ZED::recording_params> StereolabsToSennet(
	const Sennet::Ref<sl::RecordingParameters> sl_rp)
{
	return Sennet::CreateRef<Sennet::ZED::recording_params>(
		std::string(sl_rp->video_filename.get()), 
		StereolabsToSennet(sl_rp->compression_mode));
}

Sennet::Ref<Sennet::ZED::runtime_params> StereolabsToSennet(
	const Sennet::Ref<sl::RuntimeParameters> sl_rp)
{
	return Sennet::CreateRef<Sennet::ZED::runtime_params>(
		StereolabsToSennet(sl_rp->sensing_mode),
		StereolabsToSennet(sl_rp->measure3D_reference_frame),
		sl_rp->enable_depth,
		sl_rp->confidence_threshold,
		sl_rp->textureness_confidence_threshold);
}
