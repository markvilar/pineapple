#include "Sennet/ZED/Panels/InitParametersPanel.hpp"

namespace Sennet { namespace ZED {

InitParametersPanel::InitParametersPanel(const Ref<InitParameters>& context)
{
	SetContext(context);
}

void InitParametersPanel::SetContext(const Ref<InitParameters>& context)
{
	m_Context = context;
}

void InitParametersPanel::OnImGuiRender()
{
	if (ImGui::CollapsingHeader("Initialization Parameters"))
	{
		if (!m_Context)
		{
			ImGui::Text("No Context Bound.");
			return;
		}

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
		ImGui::Combo("Resolution", (int*)&m_Context->resolution, 
			&FuncHolder::ItemGetter, resolutionOptions, 
			IM_ARRAYSIZE(resolutionOptions));

		const char* fpsOptions[] = { "0", "15", "30", "60", "100" };
		ImGui::Combo("Camera FPS", (int*)&m_Context->cameraFPS, 
			&FuncHolder::ItemGetter, fpsOptions, 
			IM_ARRAYSIZE(fpsOptions));

		ImGui::Checkbox("Enable Image Enhancement", 
			&m_Context->enableImageEnhancement);
		ImGui::Checkbox("Disable Self Calibration", 
			&m_Context->disableSelfCalibration);
		ImGui::Checkbox("Enable Verbose SDK", 
			&m_Context->enableVerboseSDK);
		ImGui::Checkbox("Require Sensors", 
			&m_Context->requireSensors);

		ImGui::Dummy(ImVec2(0.0f, 15.0f));
		ImGui::Text("Depth Related Initialization Parameters");

		static const char* depthModeOptions[] = { "None", "Performance", 
			"Quality", "Ultra" };
		ImGui::SliderInt("Depth Mode", (int*)&m_Context->depthMode,
			0, 3, depthModeOptions[(int)m_Context->depthMode]);

		static const char* coordUnitOptions[] = { "None", "Millimeter", 
			"Centimeter", "Meter", "Inch", "Foot" };
		ImGui::SliderInt("Coordinate Unit", 
			(int*)&m_Context->coordinateUnits, 0, 
			IM_ARRAYSIZE(coordUnitOptions) - 1, 
			coordUnitOptions[(int)m_Context->coordinateUnits]);

		static const char* coordSysOptions[] = { "None", "Image", 
			"LeftHandedYUp", "RightHandYUp", "RightHandedZUp", 
			"LeftHandedZUp", "RightHandedZUpXForward" };
		ImGui::SliderInt("Coordinate System",
			(int*)&m_Context->coordinateSystem, 0,
			IM_ARRAYSIZE(coordSysOptions) - 1,
			coordSysOptions[(int)m_Context->coordinateSystem]);

            	ImGui::SliderFloat("Minimum Depth", &m_Context->minDepth, -1.0f, 
			10000.0f, "%.1f");
		ImGui::SliderFloat("Maximum Depth", &m_Context->maxDepth, -1.0f, 
			10000.0f, "%.1f");

		ImGui::Checkbox("Enable Depth Stabilization", 
			&m_Context->enableDepthStabilization);
		ImGui::Checkbox("Enable Right Side Depth", 
			&m_Context->enableRightSideDepth);
	
		if (ImGui::SmallButton("Debug Initialization Parameters"))
		{
			SN_CORE_INFO("{0}", m_Context->ToString());
		}
	}
}

}}
