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

pine::Image convert_image(const zed::Image& image)
{
    const auto& view = image.specification.view;
    const auto image_format = [view]()
    {
        switch (view)
        {
        case zed::View::LEFT:
            return pine::ImageFormat::BGRA;
        case zed::View::RIGHT:
            return pine::ImageFormat::BGRA;
        case zed::View::LEFT_GRAY:
            return pine::ImageFormat::GRAY;
        case zed::View::RIGHT_GRAY:
            return pine::ImageFormat::GRAY;
        case zed::View::SIDE_BY_SIDE:
            return pine::ImageFormat::BGRA;
        default:
            return pine::ImageFormat::UNKNOWN;
        }
    }();
    return pine::Image(image.buffer.data(),
        image.specification.width,
        image.specification.height,
        image_format);
}

} // namespace pineapple
