#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pineapple/vendor/serializer.hpp"

namespace pineapple
{

class MemoryOutputArchive
{
    using OutputArchive = zpp::serializer::memory_output_archive;

public:
    template <typename T>
    void serialize(T& t)
    {
        m_output_archive(t);
    }

    auto& get_buffer() { return m_buffer; }

private:
    std::vector<uint8_t> m_buffer{};
    OutputArchive m_output_archive{m_buffer};
};

class MemoryInputArchive
{
    using InputArchive = zpp::serializer::memory_input_archive;

public:
    MemoryInputArchive(std::vector<uint8_t>& buffer) : m_input_archive(buffer)
    {
    }

    template <typename T>
    void deserialize(T& t)
    {
        m_input_archive(t);
    }

private:
    std::vector<uint8_t>* m_buffer{};
    InputArchive m_input_archive;
};

class MemoryViewOutputArchive
{
    using OutputArchive = zpp::serializer::memory_view_output_archive;

public:
    MemoryViewOutputArchive(uint8_t* data, const std::size_t size)
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

class MemoryViewInputArchive
{
    using InputArchive = zpp::serializer::memory_view_input_archive;

public:
    MemoryViewInputArchive(uint8_t* data, const std::size_t size)
        : m_data(data), m_size(size), m_input_archive(data, size)
    {
    }

    template <typename T>
    void deserialize(T& t)
    {
        m_input_archive(t);
    }

private:
    InputArchive m_input_archive;
    uint8_t* m_data{};
    std::size_t m_size{};
};

}; // namespace pineapple
