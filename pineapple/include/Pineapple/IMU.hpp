#pragma once

#include <Pine/Pine.hpp>

namespace Pineapple
{

struct IMUData
{
    uint64_t Timestamp;
    Pine::Vec3 Acceleration;
    Pine::Vec3 AngularVelocity;
};

} // namespace Pineapple
