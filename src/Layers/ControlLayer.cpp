#include <SennetZED/Layers/ControlLayer.hpp>

#include <imgui.h>

namespace Sennet
{

namespace ZED
{

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

void ControlLayer::RenderControlWindow()
{
	ImGui::Begin("Control");

	RenderControlExportCommandsWindow();
	RenderControlExportSettingsWindow();

	ImGui::End();
}

void ControlLayer::RenderControlExportCommandsWindow()
{
	bool collapsed = !ImGui::CollapsingHeader("Export Commands");
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

void ControlLayer::RenderControlExportSettingsWindow()
{
	bool collapsed = !ImGui::CollapsingHeader("Export Settings");
	ImGui::SameLine();
	Sennet::ImGuiHelpMarker("Export ZED sensor settings to a node or an "
		"application with an active ZED sensor layer.");

	if (collapsed)
		return;

	if (ImGui::TreeNode("InitParameters"))
	{
		RenderInitParametersTreeNode();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("RecordingParameters"))
	{
		RenderRecordingParametersTreeNode();
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("RuntimeParameters"))
	{
		RenderRuntimeParametersTreeNode();
		ImGui::TreePop();
	}
}

void ControlLayer::RenderInitParametersTreeNode()
{
	static int depthModeIndex = -1;
	const char* depthModeOptions = "Performance\0Quality\0Ultra\0";
	if (ImGui::Combo("Depth Mode", &depthModeIndex, depthModeOptions))
	{
		switch (depthModeIndex)
		{
		}
	}

	static int unitIndex = -1;
	const char* unitOptions = "Millimeter\0Centimeter\0Meter\0Inch\0Foot\0";
	if (ImGui::Combo("Coordinate Unit", &unitIndex, unitOptions))
	{
		switch (unitIndex)
		{
		}
	}

	static int coordinateSystemIndex = -1;
	const char* coordinateSystemOptions = "Image\0LeftHandedYUp\0"
		"RightHandedYUp\0RightHandedZUp\0LeftHandedZUp\0"
		"RightHandedZUpXForward\0";
	if (ImGui::Combo("Coordinate System", &coordinateSystemIndex, 
		coordinateSystemOptions))
	{
		switch (coordinateSystemIndex)
		{
		}
	}

	static bool depthStabilization = true;
	ImGui::Checkbox("Depth Stabilization", &depthStabilization);

	static float minDepth = 0;
	ImGui::SliderFloat("Min. Depth [mm]", &minDepth, 100.0f, 3000.0f, "%.0f");

	static float maxDepth = 0;
	ImGui::SliderFloat("Max. Depth [mm]", &maxDepth, 100.0f, 3000.0f, "%.0f");

	static bool enableRightSideDepth = false;
	ImGui::Checkbox("Enable Right Side Depth", &enableRightSideDepth);

	static int resolutionIndex = -1;
	const char* resolutionOptions = "HD2K\0HD1080\0HD720\0VGA\0";
	if (ImGui::Combo("Resolution", &resolutionIndex, resolutionOptions))
	{
		switch (resolutionIndex)
		{
		}
	}

	// int Camera FPS
	static int cameraFPSIndex = -1;
	const char* cameraFPSOptions = "15\0" "30\0" "60\0" "100\0";
	if (ImGui::Combo("Camera FPS", &cameraFPSIndex, cameraFPSOptions))
	{
		switch (cameraFPSIndex)
		{
		}
	}

	// bool Enable Image Enhancement
	static bool enableImageEnhancement = false;
	ImGui::Checkbox("Enable Image Enhancement", &enableImageEnhancement);

	// bool Disable Self Calibration
	static bool disableSelfCalibration = false;
	ImGui::Checkbox("Disable Self Calibration", &disableSelfCalibration);

	// bool Enable Verbose SDK
	static bool enableVerboseSDK = false;
	ImGui::Checkbox("Enable Verbose SDK", &enableVerboseSDK);

	// bool Require Sensors
	static bool requireSensors = false;
	ImGui::Checkbox("Require Sensors", &requireSensors);

	
}

void ControlLayer::RenderRecordingParametersTreeNode()
{
}

void ControlLayer::RenderRuntimeParametersTreeNode()
{
	static char addressBuffer[20];
	static char portBuffer[10];
	ImGui::InputText("Target Address", addressBuffer, 
		IM_ARRAYSIZE(addressBuffer));
	ImGui::InputText("Target Port", portBuffer, IM_ARRAYSIZE(portBuffer));
}

}
}
