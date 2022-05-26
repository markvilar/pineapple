#include "pineapple/utils.hpp"

namespace pineapple
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

Pine::Image ConvertImage(const zed::Image& image)
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
    return Pine::Image(image.buffer.data(), image.specification.width,
        image.specification.height, image_format);
}

} // namespace pineapple
