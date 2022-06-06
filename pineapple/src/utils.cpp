#include "pineapple/utils.hpp"

namespace pineapple
{

std::string current_date_time()
{
    const auto now = time(0);
    struct tm time_struct;
    std::array<char, 80> buffer;
    time_struct = *localtime(&now);
    strftime(buffer.data(), buffer.size(), "%Y-%m-%d.%X", &time_struct);
    return std::string(buffer.data(), buffer.size());
}

Pine::Image convert_image(const zed::Image& image)
{
    const auto& view = image.specification.view;
    const auto image_format = [view]()
    {
        switch (view)
        {
        case zed::View::LEFT:
            return Pine::ImageFormat::BGRA;
        case zed::View::RIGHT:
            return Pine::ImageFormat::BGRA;
        case zed::View::LEFT_GRAY:
            return Pine::ImageFormat::GRAY;
        case zed::View::RIGHT_GRAY:
            return Pine::ImageFormat::GRAY;
        case zed::View::SIDE_BY_SIDE:
            return Pine::ImageFormat::BGRA;
        default:
            return Pine::ImageFormat::UNKNOWN;
        }
    }();
    return Pine::Image(image.buffer.data(),
        image.specification.width,
        image.specification.height,
        image_format);
}

} // namespace pineapple
