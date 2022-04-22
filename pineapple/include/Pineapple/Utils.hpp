#pragma once

#include <array>
#include <ctime>
#include <string>
#include <utility>

#include <Pine/Pine.hpp>

#include "Pineapple/Zed/Types.hpp"

namespace Pineapple
{

std::string CurrentDateTime();

Pine::Image ConvertImage(const Zed::Image& image);

}; // namespace Pineapple
