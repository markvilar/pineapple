#include <SennetZED/Layers/ControlLayer.hpp>

#include <imgui.h>

namespace Sennet
{

namespace ZED
{

static unsigned short StringToUnsignedShort(const std::string s)
{
	auto number = std::strtoul(s.c_str(), NULL, 0);
	if (number > USHRT_MAX)
	{
		return 0;
	}

	return (unsigned short) number;
}

static void Print(const InitParametersData& data)
{
	SN_TRACE("Depth Mode: 				{0}", 
		data.depthMode);
	SN_TRACE("Coord. Units: 			{0}", 
		data.coordinateUnits);
	SN_TRACE("Coord. System: 			{0}", 
		data.coordinateSystem);
	SN_TRACE("Depth Stabilization: 			{0}", 
		data.enableDepthStabilization);
	SN_TRACE("Min. Depth: 				{0}", 
		data.minDepth);
	SN_TRACE("Max. Depth: 				{0}", 
		data.maxDepth);
	SN_TRACE("Enable Right Side Depth: 		{0}", 
		data.enableRightSideDepth);
	SN_TRACE("Resolution: 				{0}", 
		data.resolution);
	SN_TRACE("Camera FPS: 				{0}", 
		data.cameraFPS);
	SN_TRACE("Enable Image Enhancement: 		{0}", 
		data.enableImageEnhancement);
	SN_TRACE("Disable Self Calibration: 		{0}", 
		data.disableSelfCalibration);
	SN_TRACE("Enable Verbose SDK: 			{0}", 
		data.enableVerboseSDK);
	SN_TRACE("Require Sensors: 			{0}", 
		data.requireSensors);
}

static void Print(const RecordingParametersData& data)
{
	SN_TRACE("SVO filename: 			{0}", data.filename);
	SN_TRACE("SVO Compression Mode: 		{0}", 
		data.compressionMode);
}

static void Print(const RuntimeParametersData& data)
{
	SN_TRACE("Sensing Mode: 			{0}", 
		data.sensingMode);
	SN_TRACE("Reference Frame: 			{0}", 
		data.referenceFrame);
	SN_TRACE("Enable Depth: 			{0}", 
		data.enableDepth);
	SN_TRACE("Confidence threshold:			{0}", 
		data.confidenceThreshold);
	SN_TRACE("Texture confidence threshold:		{0}", 
		data.textureConfidenceThreshold);
}

ControlLayer::ControlLayer()
	: Layer("Information") 
{
}

ControlLayer::~ControlLayer()
{
}

void ControlLayer::OnAttach()
{
}

void ControlLayer::OnDetach()
{
}

void ControlLayer::OnUpdate(Timestep ts)
{
}

void ControlLayer::OnImGuiRender()
{
	RenderControlWindow();
}

void ControlLayer::OnEvent(Event& event)
{
}

void ControlLayer::OnMessage(Ref<Message> msg)
{
	MessageDispatcher dispatcher(msg);
	dispatcher.Dispatch<CommandResponse>(
		std::bind(&ControlLayer::OnCommandResponse, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<SettingsResponse>(
		std::bind(&ControlLayer::OnSettingsResponse, this, 
		std::placeholders::_1));
	dispatcher.Dispatch<StateResponse>(
		std::bind(&ControlLayer::OnStateResponse, this, 
		std::placeholders::_1));
}

bool ControlLayer::OnCommandResponse(Ref<CommandResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

bool ControlLayer::OnSettingsResponse(Ref<SettingsResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

bool ControlLayer::OnStateResponse(Ref<StateResponse> msg)
{
	SN_TRACE("[ControlLayer] {0}", msg->GetMessageType());
	return true;
}

void ControlLayer::SubmitCommandRequest(const std::string address,
	const std::string port)
{
	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (connectionManager)
	{
	}
	else
	{
		SN_WARN("Connection manager not initialized!");
			
	}
}

void ControlLayer::SubmitSettingsRequest(const std::string address,
	const std::string port)
{
	//Print(m_InitData);
	//Print(m_RecordingData);
	//Print(m_RuntimeData);

	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (connectionManager)
	{
		auto connection = connectionManager->FindConnection(address,
			StringToUnsignedShort(port));
		if (connection)
		{
			InitParameters initParameters(m_InitData);
			RecordingParameters recordingParameters(m_RecordingData);
			RuntimeParameters runtimeParameters(m_RuntimeData);

			auto msg = Sennet::CreateRef<SettingsRequest>(
				connection->GetLocalInformation().first,
				connection->GetLocalInformation().second,
				initParameters, 
				recordingParameters,
				runtimeParameters);
			connectionManager->SubmitMessage(connection, msg);
			SN_TRACE("Sent message {0} to {1}:{2}", 
				msg->ToString(),
				connection->GetRemoteInformation().first,
				connection->GetRemoteInformation().second);
		}
		else
		{
			SN_WARN("Could not find connection with remote "
				"endpoint: {0}:{1}", address, port);
		}
	}
	else
	{
		SN_WARN("Connection manager not initialized!");
	}
}

void ControlLayer::SubmitStateRequest(const std::string address,
	const std::string port)
{
	auto connectionManager = Sennet::ConnectionManager::GetPtr();
	if (connectionManager)
	{
		SN_TRACE("SubmitStateRequest: Got connection manager.");
	}
	else
	{
		SN_WARN("SubmitStateRequest: Connection manager not "
			"initialized!");
	}
}


void ControlLayer::RenderControlWindow()
{
	ImGui::Begin("Control");

	RenderCommandsHeader();
	RenderSettingsHeader();

	ImGui::End();
}

void ControlLayer::RenderCommandsHeader()
{
	bool collapsed = !ImGui::CollapsingHeader("Commands");
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Export ZED sensor commands to a node or an "
		"application with an active ZED sensor layer.");

	if (collapsed)
		return;

	static char addressBuffer[20];
	static char portBuffer[10];
	ImGui::InputText("Target Address", addressBuffer, 
		IM_ARRAYSIZE(addressBuffer));
	ImGui::InputText("Target Port", portBuffer, IM_ARRAYSIZE(portBuffer));
}

void ControlLayer::RenderSettingsHeader()
{
	bool collapsed = !ImGui::CollapsingHeader("Settings");
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Export ZED sensor settings to a node or an "
		"application with an active ZED sensor layer.");

	if (collapsed)
		return;

	if (ImGui::TreeNode("InitParameters"))
	{
		RenderSettingsInitParametersNode();
		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("RecordingParameters"))
	{
		RenderSettingsRecordingParametersNode();
		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("RuntimeParameters"))
	{
		RenderSettingsRuntimeParametersNode();
		ImGui::TreePop();
	}
	ImGui::Separator();

	if (ImGui::TreeNode("Settings Submission"))
	{
		RenderSettingsSubmissionNode();
		ImGui::TreePop();
	}
}

void ControlLayer::RenderSettingsInitParametersNode()
{
	const char* depthModeOptions = "None\0Performance\0Quality\0Ultra\0";
	if (ImGui::Combo("Depth Mode", (int*)&m_InitData.depthMode, 
		depthModeOptions))
	{
	}

	const char* unitOptions = "None\0Millimeter\0Centimeter\0Meter\0Inch\0"
		"Foot\0";
	if (ImGui::Combo("Coordinate Unit", (int*)&m_InitData.coordinateUnits, 
		unitOptions))
	{
		switch (m_InitData.coordinateUnits)
		{
			case Sennet::ZED::Unit::Millimeter:
				break;
			case Sennet::ZED::Unit::Centimeter:
				break;
			case Sennet::ZED::Unit::Meter:
				break;
			case Sennet::ZED::Unit::Inch:
				break;
			case Sennet::ZED::Unit::Foot:
				break;
			default:
				break;
		}
	}

	const char* coordinateSystemOptions = "None\0Image\0LeftHandedYUp\0"
		"RightHandedYUp\0RightHandedZUp\0LeftHandedZUp\0"
		"RightHandedZUpXForward\0";
	if (ImGui::Combo("Coordinate System", 
		(int*)&m_InitData.coordinateSystem, 
		coordinateSystemOptions))
	{
	}

	ImGui::Checkbox("Enable Depth Stabilization", 
		&m_InitData.enableDepthStabilization);

	// TODO: Revise. Depends on coordinate unit.
	ImGui::SliderFloat("Min. Depth [mm]", &m_InitData.minDepth, 100.0f, 
		3000.0f, "%.0f");

	ImGui::SliderFloat("Max. Depth [mm]", &m_InitData.maxDepth, 100.0f, 
		3000.0f, "%.0f");

	ImGui::Checkbox("Enable Right Side Depth", 
		&m_InitData.enableRightSideDepth);

	const char* resolutionOptions = "None\0HD2K\0HD1080\0HD720\0VGA\0";
	if (ImGui::Combo("Resolution", (int*)&m_InitData.resolution, 
		resolutionOptions))
	{
		switch (m_InitData.resolution)
		{
			case Sennet::ZED::Resolution::HD2K:
				break;
			case Sennet::ZED::Resolution::HD1080:
				break;
			case Sennet::ZED::Resolution::HD720:
				break;
			case Sennet::ZED::Resolution::VGA:
				break;
			default:
				break;
		}
	}

	// TODO: Revise. Depends upon resolution!
	const char* cameraFPSOptions = "15\0" "30\0" "60\0" "100\0";
	if (ImGui::Combo("Camera FPS", &m_InitData.cameraFPS, cameraFPSOptions))
	{
		switch (m_InitData.cameraFPS)
		{
		}
	}

	ImGui::Checkbox("Enable Image Enhancement", 
		&m_InitData.enableImageEnhancement);
	ImGui::Checkbox("Disable Self Calibration", 
		&m_InitData.disableSelfCalibration);
	ImGui::Checkbox("Enable Verbose SDK", &m_InitData.enableVerboseSDK);
	ImGui::Checkbox("Require Sensors", &m_InitData.requireSensors);
}

void ControlLayer::RenderSettingsRecordingParametersNode()
{
	ImGui::InputText("SVO Filename", m_RecordingData.filename.data(), 
		m_RecordingData.filename.size());

	const char* compressionModeOptions = "None\0Lossless\0H264\0H265\0";
	if (ImGui::Combo("SVO Compression Mode", 
		(int*)&m_RecordingData.compressionMode, 
		compressionModeOptions))
	{
		switch (m_RecordingData.compressionMode)
		{
			case Sennet::ZED::SVOCompressionMode::Lossless:
				break;
			case Sennet::ZED::SVOCompressionMode::H264:
				break;
			case Sennet::ZED::SVOCompressionMode::H265:
				break;
			case Sennet::ZED::SVOCompressionMode::None:
				break;
		}
	}
}

void ControlLayer::RenderSettingsRuntimeParametersNode()
{
	const char* sensingModeOptions = "None\0Standard\0Fill\0";
	if (ImGui::Combo("Depth Sensing Mode", 
		(int*)&m_RuntimeData.sensingMode,
		sensingModeOptions))
	{
		switch (m_RuntimeData.sensingMode)
		{
			case Sennet::ZED::SensingMode::Standard:
				SN_TRACE("Standard");
				break;
			case Sennet::ZED::SensingMode::Fill:
				SN_TRACE("Fill");
				break;
			case Sennet::ZED::SensingMode::None:
				SN_TRACE("None");
				break;
		}
	}

	const char* referenceFrameOptions = "None\0World\0Camera\0";
	if (ImGui::Combo("Depth Reference Frame", 
		(int*)&m_RuntimeData.referenceFrame, 
		referenceFrameOptions))
	{
		switch (m_RuntimeData.referenceFrame)
		{
			case Sennet::ZED::ReferenceFrame::World:
				break;
			case Sennet::ZED::ReferenceFrame::Camera:
				break;
			case Sennet::ZED::ReferenceFrame::None:
				break;
		}
	}
	
	ImGui::Checkbox("Enable Depth", &m_RuntimeData.enableDepth);
	ImGui::SliderInt("Confidence Threshold", 
		&m_RuntimeData.confidenceThreshold, 1, 100, "%d");
	ImGui::SliderInt("Texture Confidence Threshold", 
		&m_RuntimeData.textureConfidenceThreshold, 1, 100, "%d");
}

void ControlLayer::RenderSettingsSubmissionNode()
{
	static char addressBuffer[20];
	static char portBuffer[10];
	ImGui::InputText("Target Address", addressBuffer, 
		IM_ARRAYSIZE(addressBuffer));
	ImGui::InputText("Target Port", portBuffer, IM_ARRAYSIZE(portBuffer));
	if (ImGui::Button("Submit Settings"))
	{
		SubmitSettingsRequest(addressBuffer, portBuffer);
	}
}

}
}
