#pragma once

namespace pineapple
{

struct StreamConfig
{
    uint16_t width = 1280;
    uint16_t height = 720;
    float period = 0.5f;
};

inline bool operator==(const StreamConfig& lhs, const StreamConfig& rhs)
{
    return lhs.width == rhs.width 
        && lhs.height == rhs.height 
        && lhs.period == rhs.period;
}

inline bool operator!=(const StreamConfig& lhs, const StreamConfig& rhs)
{
    return !(lhs == rhs);
}

}; // namespace pineapple
