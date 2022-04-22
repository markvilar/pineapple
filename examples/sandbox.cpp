#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <Pine/Pine.hpp>

#include "Pineapple/Zed/Protocol.hpp"
#include "Pineapple/Zed/Types.hpp"

#include "Pineapple/Message.hpp"
#include "Pineapple/Serialization.hpp"

void TestControlSerialization()
{
    std::vector<std::uint8_t> buffer;
    zpp::serializer::memory_output_archive output_archive(buffer);
    zpp::serializer::memory_input_archive input_archive(buffer);

    PINE_INFO("\nTest control serialization:");

    // Serialization
    Pineapple::Zed::ControlRequest request;
    request.action = Pineapple::Zed::CameraAction::START_RECORD;
    request.parameters.resolution = Pineapple::Zed::Resolution::HD1080;
    PINE_INFO("Original: {0}, {1}", request.action, 
        request.parameters.resolution);
    output_archive(request);

    // Deserialization
    Pineapple::Zed::ControlRequest new_request;
    input_archive(new_request);
    PINE_INFO("New: {0}, {1}", new_request.action, 
        new_request.parameters.resolution);
}

void TestImageSerialization()
{
    std::vector<std::uint8_t> buffer;
    zpp::serializer::memory_output_archive output_archive(buffer);
    zpp::serializer::memory_input_archive input_archive(buffer);

    PINE_INFO("\nTest image serialization:");

    // Serialization
    const auto width = 32;
    const auto height = 32;
    const auto channels = 4;
    Pineapple::Zed::Image output_image;
    output_image.specification.width = width;
    output_image.specification.height = height;
    output_image.specification.view = Pineapple::Zed::View::LEFT;
    output_image.buffer = [width, height, channels](){
        std::vector<uint8_t> v(width*height*channels, 0);
        return v;
    }();
    PINE_INFO("Output image: {0}, {1}, {2}, {3}", 
        output_image.specification.width, 
        output_image.specification.height,
        output_image.specification.view,
        output_image.buffer.size());
    output_archive(output_image);

    // Deserialization
    Pineapple::Zed::Image input_image;
    input_archive(input_image);
    PINE_INFO("Input image: {0}, {1}, {2}, {3}", 
        input_image.specification.width, 
        input_image.specification.height,
        input_image.specification.view,
        input_image.buffer.size());
}

void TestMessageSerialization()
{
    std::vector<std::uint8_t> buffer;
    zpp::serializer::memory_output_archive output_archive(buffer);

    PINE_INFO("\nTest message serialization:");

    Pineapple::HeadedMessage<Pineapple::Zed::MessageIdentifier, 
        Pineapple::Zed::ControlRequest> message;

    message.header = Pineapple::Zed::MessageIdentifier::ControlRequest;
    message.body.action = Pineapple::Zed::CameraAction::START_RECORD;

    output_archive(message);

    PINE_INFO("Serialized message: {0}, {1}", buffer.size(),
        std::string(buffer.begin(), buffer.end()));
}

int main(int argc, char** argv)
{
    Pine::Log::Init();

    TestControlSerialization();
    TestImageSerialization();
    TestMessageSerialization();
    return 0;
}
