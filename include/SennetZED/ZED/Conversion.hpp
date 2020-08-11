#pragma once

#include <memory>

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

// Conversion function from Sennet::ZED types to sl types.
sl::VIEW SennetToStereolabs(const Sennet::ZED::view& sn_view);
sl::RESOLUTION SennetToStereolabs(const Sennet::ZED::resolution& sn_res);
sl::VIDEO_SETTINGS SennetToStereolabs(
	const Sennet::ZED::video_settings& sn_video);
sl::DEPTH_MODE SennetToStereolabs(const Sennet::ZED::depth_mode& sn_depth);
sl::UNIT SennetToStereolabs(const Sennet::ZED::unit& sn_unit);
sl::SVO_COMPRESSION_MODE SennetToStereolabs(
	const Sennet::ZED::svo_compression_mode& sn_compr);
sl::SENSING_MODE SennetToStereolabs(
	const Sennet::ZED::sensing_mode& sn_sensing);
sl::REFERENCE_FRAME SennetToStereolabs(
	const Sennet::ZED::reference_frame& sn_ref);
sl::COORDINATE_SYSTEM SennetToStereolabs(
	const Sennet::ZED::coordinate_system& sn_sys);

// Conversion function from Sennet::ZED classes to sl classes.
Sennet::Ref<sl::Mat> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::image> sn_img);
Sennet::Ref<sl::InitParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::init_params> sn_ip);
Sennet::Ref<sl::RecordingParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::recording_params> sn_rp);
Sennet::Ref<sl::RuntimeParameters> SennetToStereolabs(
	const Sennet::Ref<Sennet::ZED::runtime_params> sn_rp);

// Conversion function from sl types to Sennet::ZED types.
Sennet::ZED::view StereolabsToSennet(const sl::VIEW& sl_view);
Sennet::ZED::resolution StereolabsToSennet(const sl::RESOLUTION& sl_res);
Sennet::ZED::video_settings StereolabsToSennet(
	const sl::VIDEO_SETTINGS& sl_video);
Sennet::ZED::depth_mode StereolabsToSennet(const sl::DEPTH_MODE& sl_depth);
Sennet::ZED::unit StereolabsToSennet(const sl::UNIT& sl_unit);
Sennet::ZED::svo_compression_mode StereolabsToSennet(
	const sl::SVO_COMPRESSION_MODE& sl_compr);
Sennet::ZED::sensing_mode StereolabsToSennet(
	const sl::SENSING_MODE& sl_sensing);
Sennet::ZED::reference_frame StereolabsToSennet(
	const sl::REFERENCE_FRAME& sl_ref);
Sennet::ZED::coordinate_system StereolabsToSennet(
	const sl::COORDINATE_SYSTEM& sl_sys);

// Conversion function from sl classes to Sennet::ZED classes.
Sennet::Ref<Sennet::ZED::image> StereolabsToSennet(
	const Sennet::Ref<sl::Mat> sl_img);
Sennet::Ref<Sennet::ZED::init_params> StereolabsToSennet(
	const Sennet::Ref<sl::InitParameters> sl_ip);
Sennet::Ref<Sennet::ZED::recording_params> StereolabsToSennet(
	const Sennet::Ref<sl::RecordingParameters> sl_rp);
Sennet::Ref<Sennet::ZED::runtime_params> StereolabsToSennet(
	const Sennet::Ref<sl::RuntimeParameters> sl_rp);
