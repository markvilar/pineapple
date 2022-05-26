#pragma once

#include <array>
#include <ctime>
#include <string>
#include <utility>

#include <Pine/Pine.hpp>

#include "pineapple/zed/types.hpp"

namespace pineapple
{

std::string CurrentDateTime();

Pine::Image ConvertImage(const zed::Image& image);

}; // namespace pineapple
