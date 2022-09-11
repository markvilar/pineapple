#pragma once

#include <typeinfo>
#include <typeindex>
#include <type_traits>

#include "pineapple/serialization.hpp"

namespace pineapple
{

struct MessageHeader
{
    uint32_t id{};
    uint32_t size{};
};

class Message
{
public:
    void* data() { return body.data(); }
    const void* data() const { return body.data(); }

    size_t size() { return body.size(); }
    const size_t size() const { return body.size(); }

    template <typename T>
    void push(const T& t)
    {
	    static_assert(std::is_standard_layout<T>::value,
			"Type is too complex to be pushed into message.");
        
        uint64_t current_size = body.size();
		body.resize(body.size() + sizeof(T));
		std::memcpy(body.data() + current_size, &t, sizeof(T));
		header.size = body.size();
    }

    template <typename T>
    void push(const T* t, const size_t size)
    {
		static_assert(std::is_standard_layout<T>::value,
			"Type is too complex to be pushed into message.");
	
        uint64_t current_size = body.size();
		body.resize(current_size + size);
		std::memcpy(body.data() + current_size, t, size);
		header.size = body.size();
    }

    template <typename T>
    void pop(T& t)
    {
        static_assert(std::is_standard_layout<T>::value,
			"Type is too complex to be pushed into message.");
		
        uint64_t new_size = body.size() - sizeof(T);
		std::memcpy(&t, body.data() + new_size, sizeof(T));
		body.resize(new_size);
		header.size = body.size();
    }

    template <typename T>
    void pop(T* t, size_t size)
    {
        static_assert(std::is_standard_layout<T>::value,
			"Type is too complex to be pushed into message.");

		uint64_t new_size = body.size() - size;
		std::memcpy(t, body.data() + new_size, size);
        body.resize(new_size);
		header.size = body.size();
    }

    const std::vector<uint8_t>& get_buffer() const
    {
        return body;
    }

public:
    MessageHeader header;
    std::vector<uint8_t> body;
};

}; // namespace pineapple
