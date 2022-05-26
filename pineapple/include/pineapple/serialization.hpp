#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pineapple/vendor/serializer.hpp"

namespace pineapple
{

class MemoryArchive
{
    using OutputArchive = zpp::serializer::memory_output_archive;
    using InputArchive = zpp::serializer::memory_input_archive;

public:
    template <typename T>
    void serialize(T& t)
    {
        m_output_archive(t);
    }
    
    template <typename T>
    void deserialize(T& t)
    {
        m_input_archive(t);
    }

    auto get_buffer_data()
    {
        return m_buffer.data();
    }

    auto get_buffer_size()
    {
        return m_buffer.data();
    }

private:
    std::vector<uint8_t> m_buffer{};
    OutputArchive m_output_archive{m_buffer};
    InputArchive m_input_archive{m_buffer};
};

class ViewSerializer
{
    using OutputArchive = zpp::serializer::memory_view_output_archive;

public:
    ViewSerializer(uint8_t* data, const std::size_t size)
        : m_data(data), m_size(size), m_output_archive(data, size)
    {
    }

    template <typename T>
    void serialize(T& t)
    {
        m_output_archive(t);
    }
    
private:
    OutputArchive m_output_archive;
    uint8_t* m_data{};
    std::size_t m_size{};
};

}; // namespace pineapple
