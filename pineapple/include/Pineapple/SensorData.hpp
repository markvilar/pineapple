#pragma once

#include <chrono>
#include <deque>
#include <utility>

#include <Pine/Pine.hpp>

namespace Pineapple
{

class Timestamp
{
public:
    Timestamp()
    {
        std::chrono::time_point<std::chrono::steady_clock> now 
            = std::chrono::steady_clock::now();
        const auto duration = now.time_since_epoch();
        m_Nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    Timestamp(const Timestamp&) = default;
    Timestamp(Timestamp&&) = default;

    Timestamp& operator=(const Timestamp&) = default;
    Timestamp& operator=(Timestamp&&) = default;

    ~Timestamp() = default;

    float seconds() const
    {
        return float(m_Nanoseconds) / 1e9;
    }

    float milliseconds() const
    {
        return float(m_Nanoseconds) / 1000000.0f;
    }

    float microseconds() const
    {
        return float(m_Nanoseconds) / 1000.0f;
    }

private:
    uint64_t m_Nanoseconds{};
};

struct SensorData
{
    float Pressure; // [Pa]
    float TemperatureLeft; // [degC]
    float TemperatureRight; // [degC]
    Pine::Vec3 Acceleration{0.0f}; // [m/s^2]
    Pine::Vec3 AngularVelocity{0.0f}; // [deg/s]
};

template <typename T, size_t N>
class StaticSeries
{
public:
    void push_back(const T& t)
    {
        m_Buffer[m_Offset] = t;
        m_Offset = (m_Offset + 1) % N;
    }

    T* data()
    {
        return m_Buffer.data();
    }

    T* data() const
    {
        return m_Buffer.data();
    }

    size_t size() const
    {
        return m_Buffer.size();
    }

    size_t offset() const
    {
        return m_Offset;
    }

private:
    std::array<T, N> m_Buffer;
    size_t m_Offset{0};
};

} // namespace Pineapple
