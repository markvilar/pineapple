#include "Sennet-ZED/Panels/InitParametersPanel.hpp"

namespace Sennet { namespace ZED {

void InitParametersPanel::SetClient(const Ref<Client>& client)
{
	m_Client = client;
}

void InitParametersPanel::SetServerParameters(
	const Ref<InitParameters>& parameters)
{
	m_ServerParameters = parameters;
}

void InitParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Initialization Parameters"))
	{
		ImGui::Text("Generic Parameters");

		const char* resLabels[] = { "None", "HD2K", "HD1080", "HD720",
			"VGA" };
		Resolution resOptions[] = { Resolution::None, Resolution::HD2K,
			Resolution::HD1080, Resolution::HD720, Resolution::VGA };
		static_assert(sizeof(resLabels) / sizeof(resLabels[0])
			== sizeof(resOptions) / sizeof(resOptions[0]),
			"Resolution labels and options must be of equal size.");
		static int resIndex = 3;
		const char* resLabel = resLabels[resIndex];
		if (ImGui::BeginCombo("Resolution", resLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(resLabels); n++)
			{
				const bool isSelected = (m_Parameters.resolution 
					== resOptions[n]);
				if (ImGui::Selectable(resLabels[n], isSelected))
				{
					resIndex = n;
					m_Parameters.resolution = resOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		const char* fpsLabels[] = { "Auto", "15", "30", "60", "100" };
		int fpsOptions[] = { 0, 15, 30, 60, 100 };
		static_assert(sizeof(fpsLabels) / sizeof(fpsLabels[0])
			== sizeof(fpsOptions) / sizeof(fpsOptions[0]),
			"FPS labels and options must be of equal size.");
		static int fpsIndex = 0;
		const char* fpsLabel = fpsLabels[fpsIndex];
		if (ImGui::BeginCombo("Camera FPS", fpsLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(fpsLabels); n++)
			{
				const bool isSelected = (m_Parameters.cameraFPS
					== fpsOptions[n]);
				if (ImGui::Selectable(fpsLabels[n], isSelected))
				{
					fpsIndex = n;
					m_Parameters.cameraFPS = fpsOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::Checkbox("Enable Image Enhancement", 
			&m_Parameters.enableImageEnhancement);
		ImGui::Checkbox("Disable Self Calibration", 
			&m_Parameters.disableSelfCalibration);
		ImGui::Checkbox("Enable Verbose SDK", 
			&m_Parameters.enableVerboseSDK);
		ImGui::Checkbox("Require Sensors", 
			&m_Parameters.requireSensors);

		ImGui::Dummy(ImVec2(0.0f, 15.0f));
		ImGui::Text("Depth Parameters");

		const char* depthLabels[] = { "None", "Performance", "Quality", 
			"Ultra" };
		DepthMode depthOptions[] = { DepthMode::None,
			DepthMode::Performance, DepthMode::Quality,
			DepthMode::Ultra };
		static_assert(sizeof(depthLabels) / sizeof(depthLabels[0])
			== sizeof(depthOptions) / sizeof(depthOptions[0]),
			"FPS labels and options must be of equal size.");
		static int depthIndex = 3;
		const char* depthLabel = depthLabels[depthIndex];
		if (ImGui::BeginCombo("Depth Mode", depthLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(depthLabels); n++)
			{
				const bool isSelected = (m_Parameters.depthMode
					== depthOptions[n]);
				if (ImGui::Selectable(depthLabels[n], 
					isSelected))
				{
					depthIndex = n;
					m_Parameters.depthMode = depthOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		const char* unitLabels[] = { "None", "Millimeter", "Centimeter", 
			"Meter", "Inch", "Foot" };
		Unit unitOptions[] = { Unit::None, Unit::Millimeter,
			Unit::Centimeter, Unit::Meter, Unit::Inch, Unit::Foot };
		static_assert(sizeof(unitLabels) / sizeof(unitLabels[0])
			== sizeof(unitOptions) / sizeof(unitOptions[0]),
			"Coordinate unit labels and options must be of "
			"equal size.");
		static int unitIndex = 1;
		const char* unitLabel = unitLabels[unitIndex];
		if (ImGui::BeginCombo("Coordinate Units", unitLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(unitLabels); n++)
			{
				const bool isSelected = 
					(m_Parameters.coordinateUnits ==
					unitOptions[n]);
					
				if (ImGui::Selectable(unitLabels[n], 
					isSelected))
				{
					unitIndex = n;
					m_Parameters.coordinateUnits = 
						unitOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		static const char* sysLabels[] = { "None", "Image", 
			"LeftHandedYUp", "RightHandYUp", "RightHandedZUp", 
			"LeftHandedZUp", "RightHandedZUpXForward" };
		CoordinateSystem sysOptions[] = { CoordinateSystem::None, 
			CoordinateSystem::Image,
			CoordinateSystem::LeftHandedYUp, 
			CoordinateSystem::RightHandedYUp, 
			CoordinateSystem::RightHandedZUp, 
			CoordinateSystem::LeftHandedZUp, 
			CoordinateSystem::RightHandedZUpXForward };
		static_assert(sizeof(sysLabels) / sizeof(sysLabels[0])
			== sizeof(sysOptions) / sizeof(sysOptions[0]),
			"Coordinate system labels and options must be of "
			"equal size.");
		static int sysIndex = 1;
		const char* sysLabel = sysLabels[sysIndex];
		if (ImGui::BeginCombo("Coordinate System", sysLabel))
		{
			for (int n = 0; n < IM_ARRAYSIZE(sysLabels); n++)
			{
				const bool isSelected = 
					(m_Parameters.coordinateSystem ==
					sysOptions[n]);
					
				if (ImGui::Selectable(sysLabels[n], 
					isSelected))
				{
					sysIndex = n;
					m_Parameters.coordinateSystem = 
						sysOptions[n];
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

            	ImGui::SliderFloat("Minimum Depth", &m_Parameters.minDepth, 
			-1.0f, m_Parameters.maxDepth, "%.1f");
		ImGui::SliderFloat("Maximum Depth", &m_Parameters.maxDepth, 
			m_Parameters.minDepth, 10000.0f, "%.1f");

		ImGui::Checkbox("Enable Depth Stabilization", 
			&m_Parameters.enableDepthStabilization);
		ImGui::Checkbox("Enable Right Side Depth", 
			&m_Parameters.enableRightSideDepth);

		if (ImGui::SmallButton("Send Initialization Parameters"))
		{
			if (m_Client && m_Client->IsConnected())
			{
				m_Client->RequestInitParametersUpdate(
					m_Parameters);
			}
		}
	
		if (ImGui::SmallButton("Debug Initialization Parameters"))
		{
			SN_CORE_INFO("{0}", m_Parameters.ToString());
		}
	}
}

}}
