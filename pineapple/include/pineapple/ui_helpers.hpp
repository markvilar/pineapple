#pragma once

#include <pine/pine.hpp>

#include "pineapple/zed/types.hpp"

namespace pineapple
{

template <typename T, size_t N>
class StaticSeries
{
public:
    void push_back(const T& t)
    {
        m_buffer[m_offset] = t;
        m_offset = (m_offset + 1) % N;
    }

    T* data() { return m_buffer.data(); }

    T* data() const { return m_buffer.data(); }

    size_t size() const { return m_buffer.size(); }

    size_t offset() const { return m_offset; }

private:
    std::array<T, N> m_buffer;
    size_t m_offset{0};
};

void draw_camera_parameters(zed::CameraParameters& parameters);
void draw_camera_settings(zed::CameraSettings& settings);
void draw_image_specification(zed::ImageSpecification& specifications);

}; // namespace pineapple
