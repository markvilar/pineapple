#include "Pineapple/Utils.hpp"

namespace Pineapple
{

std::string CurrentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

} // namespace Pineapple
