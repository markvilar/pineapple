#include "pineapple/utils.hpp"

namespace pineapple
{

std::string current_date_time()
{
    const auto now = time(0);
    struct tm time_struct;
    char buffer[80];
    time_struct = *localtime(&now);
    strftime(buffer, 80, "%Y%m%d_%H%M%S", &time_struct);
    return std::string(buffer);
}

} // namespace pineapple
