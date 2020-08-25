#include <SennetZED/Primitives/IO.hpp>

std::ostream& operator<<(std::ostream& os, const sl::String& s)
{
	os << s.get();
	return os;
}

std::ostream& operator<<(std::ostream& os, const sl::InitParameters& params)
{
	os << "InitParameters:\n";
	os << " - Resolution:              " << params.camera_resolution << "\n";
	os << " - Fps:                     " << params.camera_fps << "\n";
	os << " - Image flip:              " << params.camera_image_flip << "\n";
	os << " - Svo real time mode:      " 
		<< params.svo_real_time_mode << "\n";
	os << " - Depth mode:              " 
		<< params.depth_mode << "\n";
	os << " - Depth stabilization:     " 
		<< params.depth_stabilization << "\n";
	os << " - Depth minimum dist.:     " 
		<< params.depth_minimum_distance << "\n";
	os << " - Depth maximum dist.:     " 
		<< params.depth_maximum_distance << "\n";
	os << " - Unit:                    " << params.coordinate_units << "\n";
	os << " - Coordinate system:       " << params.coordinate_system << "\n";
	os << " - SDK gpu id:              " << params.sdk_gpu_id << "\n";
	os << " - SDK verbose:             " << params.sdk_verbose << "\n";
	os << " - Sensors required:        " << params.sensors_required << "\n";
	os << " - Enable image enh.:       " 
		<< params.enable_image_enhancement << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const sl::RuntimeParameters& params)
{
	os << "RuntimeParameters:\n";
	os << " - Sensing mode:            " << params.sensing_mode << "\n";
	os << " - 3D reference frame:      " 
		<< params.measure3D_reference_frame << "\n";
	os << " - Enable depth:            " << params.enable_depth << "\n";
	os << " - Conf. thresh.:           " 
		<< params.confidence_threshold << "\n";
	os << " - Texture conf. thresh.:   " 
		<< params.textureness_confidence_threshold << "\n";
	return os;
}

std::ostream& operator<<(
	std::ostream& os, 
	const sl::RecordingParameters& params
	)
{
	os << "RecordingParamters:\n";
	os << " - Filename: 		" << params.video_filename << "\n";
	os << " - Compression mode:	" << params.compression_mode << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const sl::CameraInformation& params)
{
	os << "CameraInformation:\n";
	os << " - Serial number:           " << params.serial_number << "\n";
	os << " - Camera firmware version: " 
		<< params.camera_firmware_version << "\n";
	os << " - Sensor firmware version: " 
		<< params.sensors_firmware_version << "\n";
	os << " - Camera model:            " << params.camera_model << "\n";
	os << " - Input type:              " 
		<< params.input_type << "\n";
	os << " - Fps:                     " << params.camera_fps << "\n";
	os << " - Resolution:              " << params.camera_resolution << "\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const sl::Resolution& res)
{
	os << res.width << "x" << res.height << " (WxH)\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const sl::Mat& m)
{
	os << "(" << m.getWidth() << "," << m.getHeight() << "," 
		<< m.getChannels() << ")"
		<< ", type: " << m.getDataType()
		<< ", memory: " << m.getMemoryType()
		<< ", step: " << m.getStep() << "\n"
		<< "width bytes: " << m.getWidthBytes()
		<< ", pixel bytes: " << m.getPixelBytes()
		<< ", step bytes: " << m.getStepBytes();
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector2<unsigned char> vs)
{
	os << "[" << static_cast<int>(vs[0]) 
		<< ", " << static_cast<int>(vs[1]) << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector3<unsigned char> vs)
{
	os << "[" << static_cast<int>(vs[0]) 
		<< ", " << static_cast<int>(vs[1])
		<< ", " << static_cast<int>(vs[2]) << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector4<unsigned char> vs)
{
	os << "[" << static_cast<int>(vs[0]) 
		<< ", " << static_cast<int>(vs[1])
		<< ", " << static_cast<int>(vs[2])
		<< ", " << static_cast<int>(vs[3]) << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector2<float> vs)
{
	os << "[" << vs[0] << ", " << vs[1] << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector3<float> vs)
{
	os << "[" << vs[0] << ", " << vs[1] << ", " << vs[2] << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, sl::Vector4<float> vs)
{
	os << "[" << vs[0] << ", " << vs[1] << ", " << vs[2] << ", " << vs[3]
		<< "]";
	return os;
}
