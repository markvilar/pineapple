#include "Pineapple/Utils.hpp"

namespace Pineapple
{

std::string CurrentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

bool SliderScalar(const std::string& name, 
    int8_t* value, 
    const int8_t minValue,
    const int8_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_S8, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    uint8_t* value, 
    const uint8_t minValue,
    const uint8_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_U8, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    int16_t* value, 
    const int16_t minValue,
    const int16_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_S16, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    uint16_t* value, 
    const uint16_t minValue,
    const uint16_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_U16, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    int32_t* value, 
    const int32_t minValue,
    const int32_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_S32, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    uint32_t* value, 
    const uint32_t minValue,
    const uint32_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_U32, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    int64_t* value, 
    const int64_t minValue,
    const int64_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_S64, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    uint64_t* value, 
    const uint64_t minValue,
    const uint64_t maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_U64, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    float* value, 
    const float minValue,
    const float maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_Float, value, 
        &minValue, &maxValue);
}

bool SliderScalar(const std::string& name, 
    double* value, 
    const double minValue,
    const double maxValue)
{
    return ImGui::SliderScalar(name.c_str(), ImGuiDataType_Double, value, 
        &minValue, &maxValue);
}

}
