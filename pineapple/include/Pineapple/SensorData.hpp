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
        return float(m_Nanoseconds) / 1000000000.0f;
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
    uint64_t m_Nanoseconds;
};

struct IMUData
{
    uint64_t Timestamp;
    Pine::Vec3 Acceleration;
    Pine::Vec3 AngularVelocity;
};

template <typename T>
class Timeseries
{
    using Pair = std::pair<Timestamp, T>;
public:
    void pop_front()
    {
        m_Data.pop_front();
    }

    void pop_back()
    {
        m_Data.pop_back();
    }

    void push_front(const Pair& pair)
    {
        m_Data.push_front(pair);
    }

    void push_back(const Pair& pair)
    {
        m_Data.push_back(pair);
    }

    size_t size() const
    {
        return m_Data.size();
    }

private:
    std::deque<Pair> m_Data;
};

} // namespace Pineapple
