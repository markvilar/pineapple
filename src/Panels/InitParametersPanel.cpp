#include "Sennet/ZED/Panels/InitParametersPanel.hpp"

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
		ImGui::Text("Generic Initialization Parameters");

		struct FuncHolder 
		{ 
			static bool ItemGetter(void* data, int idx, 
				const char** out_str) 
			{ 
				*out_str = ((const char**)data)[idx]; 
				return true; 
			} 
		};

		const char* resolutionOptions[] = { "None", "HD2K", "HD1080", 
			"HD720", "VGA"};
		ImGui::Combo("Resolution", (int*)&m_Parameters.resolution, 
			&FuncHolder::ItemGetter, resolutionOptions, 
			IM_ARRAYSIZE(resolutionOptions));

		const char* fpsOptions[] = { "0", "15", "30", "60", "100" };
		ImGui::Combo("Camera FPS", (int*)&m_Parameters.cameraFPS, 
			&FuncHolder::ItemGetter, fpsOptions, 
			IM_ARRAYSIZE(fpsOptions));

		ImGui::Checkbox("Enable Image Enhancement", 
			&m_Parameters.enableImageEnhancement);
		ImGui::Checkbox("Disable Self Calibration", 
			&m_Parameters.disableSelfCalibration);
		ImGui::Checkbox("Enable Verbose SDK", 
			&m_Parameters.enableVerboseSDK);
		ImGui::Checkbox("Require Sensors", 
			&m_Parameters.requireSensors);

		ImGui::Dummy(ImVec2(0.0f, 15.0f));
		ImGui::Text("Depth Related Initialization Parameters");

		static const char* depthModeOptions[] = { "None", "Performance", 
			"Quality", "Ultra" };
		ImGui::SliderInt("Depth Mode", (int*)&m_Parameters.depthMode,
			0, 3, depthModeOptions[(int)m_Parameters.depthMode]);

		static const char* coordUnitOptions[] = { "None", "Millimeter", 
			"Centimeter", "Meter", "Inch", "Foot" };
		ImGui::SliderInt("Coordinate Unit", 
			(int*)&m_Parameters.coordinateUnits, 0, 
			IM_ARRAYSIZE(coordUnitOptions) - 1, 
			coordUnitOptions[(int)m_Parameters.coordinateUnits]);

		static const char* coordSysOptions[] = { "None", "Image", 
			"LeftHandedYUp", "RightHandYUp", "RightHandedZUp", 
			"LeftHandedZUp", "RightHandedZUpXForward" };
		ImGui::SliderInt("Coordinate System",
			(int*)&m_Parameters.coordinateSystem, 0,
			IM_ARRAYSIZE(coordSysOptions) - 1,
			coordSysOptions[(int)m_Parameters.coordinateSystem]);

            	ImGui::SliderFloat("Minimum Depth", &m_Parameters.minDepth, 
			-1.0f, 10000.0f, "%.1f");
		ImGui::SliderFloat("Maximum Depth", &m_Parameters.maxDepth, 
			-1.0f, 10000.0f, "%.1f");

		ImGui::Checkbox("Enable Depth Stabilization", 
			&m_Parameters.enableDepthStabilization);
		ImGui::Checkbox("Enable Right Side Depth", 
			&m_Parameters.enableRightSideDepth);
	
		if (ImGui::SmallButton("Debug Initialization Parameters"))
		{
			SN_CORE_INFO("{0}", m_Parameters.ToString());
		}
	}
}

}}
