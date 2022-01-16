#pragma once

#include <array>
#include <ctime>
#include <string>
#include <utility>

#include <imgui.h>

namespace Pineapple
{

std::string CurrentDateTime();

template <typename T, size_t size, typename Callback>
void AddCombo(const std::string& name,
    const std::array<std::pair<std::string, T>, size>& items,
    const Callback callback)
{
    static uint32_t previewIndex = 0;
    const auto preview = items[previewIndex].first;

    if (ImGui::BeginCombo(name.c_str(), preview.c_str(), 0))
    {
        for (auto index = 0; index < size; index++)
        {
            const auto isSelected = (previewIndex == index);
            if (ImGui::Selectable(items[index].first.c_str(), isSelected))
                previewIndex = index;

            if (isSelected)
                ImGui::SetItemDefaultFocus();
            callback();
        }
        ImGui::EndCombo();
    }
}

bool SliderScalar(const std::string& name, int8_t* value, const int8_t minValue,
    const int8_t maxValue);

bool SliderScalar(const std::string& name, uint8_t* value,
    const uint8_t minValue, const uint8_t maxValue);

bool SliderScalar(const std::string& name, int16_t* value,
    const int16_t minValue, const int16_t maxValue);

bool SliderScalar(const std::string& name, uint16_t* value,
    const uint16_t minValue, const uint16_t maxValue);

bool SliderScalar(const std::string& name, int32_t* value,
    const int32_t minValue, const int32_t maxValue);

bool SliderScalar(const std::string& name, uint32_t* value,
    const uint32_t minValue, const uint32_t maxValue);

bool SliderScalar(const std::string& name, int64_t* value,
    const int64_t minValue, const int64_t maxValue);

bool SliderScalar(const std::string& name, uint64_t* value,
    const uint64_t minValue, const uint64_t maxValue);

bool SliderScalar(const std::string& name, float* value, const float minValue,
    const float maxValue);

bool SliderScalar(const std::string& name, double* value, const double minValue,
    const double maxValue);

}; // namespace Pineapple
