#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <sl/Camera.hpp>

#include "Pine/Pine.hpp"

#include "Pineapple/IMU.hpp"

int main(int argc, char** argv)
{
    Pine::Log::Init();

    sl::float3 s1(1.0f, 2.0f, 3.0f);
    sl::float3 s2(4.0f, 5.0f, 6.0f);

    Pine::Vec3 v1(s1[0], s1[1], s1[2]);
    Pine::Vec3 v2(s2[0], s2[1], s2[2]);

    PINE_INFO("Vector 1: {0}, {1}, {2}", v1.x, v1.y, v1.z);
    PINE_INFO("Vector 2: {0}, {1}, {2}", v2.x, v2.y, v2.z);
}
