#pragma once

#include <array>
#include <ctime>
#include <string>
#include <utility>

#include <Pine/Pine.hpp>

#include "pineapple/zed/types.hpp"

namespace pineapple
{

std::string current_date_time();

Pine::Image convert_image(const zed::Image& image);

}; // namespace pineapple
