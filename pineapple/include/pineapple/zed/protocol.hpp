#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include <pine/pine.hpp>

#include "pineapple/serialization.hpp"
#include "pineapple/zed/types.hpp"

namespace zed
{

struct ControlRequest
{
    CameraAction action;
    CameraParameters parameters;
};

struct ControlResponse
{
    CameraResponse response;
    CameraParameters parameters;
};

} // namespace zed
