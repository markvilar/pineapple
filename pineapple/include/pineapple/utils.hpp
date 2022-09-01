#pragma once

#include <array>
#include <ctime>
#include <string>
#include <utility>

#include <pine/pine.hpp>

#include "pineapple/zed/types.hpp"

namespace pineapple
{

std::string current_date_time();

pine::Image convert_image(const zed::Image& image);

}; // namespace pineapple
