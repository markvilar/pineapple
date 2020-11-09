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
		static int currentResolution= 0;
		const char* resolutionOptions[] = { "HD2K", "HD1080", "HD720", 
			"VGA"};
		ImGui::Combo("Resolution", &currentResolution, 
			&FuncHolder::ItemGetter, resolutionOptions, 
			IM_ARRAYSIZE(resolutionOptions));

		static int currentFPS = 0;
		const char* fpsOptions[] = { "15", "30", "60", "100" };
		ImGui::Combo("Camera FPS", &currentFPS, 
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

		static int currentDepthMode = 0;
		const char* depthModeOptions[] = { "None", "Performance", 
			"Quality", "Ultra" };
		ImGui::Combo("Depth Mode", &currentDepthMode, 
			&FuncHolder::ItemGetter, depthModeOptions, 
			IM_ARRAYSIZE(depthModeOptions));

		static int currentCoordinateUnit= 0;
		const char* coordinateUnitOptions[] = { "None", "Millimeter", 
			"Centimeter", "Meter", "Inch", "Foot" };
		ImGui::Combo("Coordinate Unit", &currentCoordinateUnit, 
			&FuncHolder::ItemGetter, coordinateUnitOptions, 
			IM_ARRAYSIZE(coordinateUnitOptions));

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
