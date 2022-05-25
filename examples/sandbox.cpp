#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <Pine/Pine.hpp>

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

#include "pineapple/message.hpp"
#include "pineapple/serialization.hpp"

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
    PINE_INFO("New: {0}, {1}\n", new_request.action, 
        new_request.parameters.resolution);
}

void TestImageSerialization()
{
    std::vector<std::uint8_t> buffer;
    zpp::serializer::memory_output_archive output_archive(buffer);
    zpp::serializer::memory_input_archive input_archive(buffer);

    PINE_INFO("Test image serialization:");

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
    PINE_INFO("Input image: {0}, {1}, {2}, {3}\n", 
        input_image.specification.width, 
        input_image.specification.height,
        input_image.specification.view,
        input_image.buffer.size());
}

void TestMessageSerialization()
{
    std::vector<std::uint8_t> request_buffer;
    zpp::serializer::memory_output_archive 
        request_output_archive(request_buffer);

    PINE_INFO("Test message serialization:");

    Pineapple::Message<Pineapple::Zed::MessageIdentifier, 
        Pineapple::Zed::ControlRequest> control_request_message;

    control_request_message.header 
        = Pineapple::Zed::MessageIdentifier::ControlRequest;
    control_request_message.body.action 
        = Pineapple::Zed::CameraAction::START_RECORD;

    request_output_archive(control_request_message);

    PINE_INFO("Serialized control request: {0}, {1}", request_buffer.size(),
        std::string(request_buffer.begin(), request_buffer.end()));

    // TODO: Read identifier from buffer and try to deserialize.
    Pineapple::Zed::MessageIdentifier identifier;
    zpp::serializer::memory_input_archive input_archive(request_buffer);
    input_archive(identifier);
    PINE_INFO("Deserialized identifier: {0}", identifier);

    if (identifier == Pineapple::Zed::MessageIdentifier::Unknown)
    {
        PINE_INFO("Got unknown message.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::ControlRequest)
    {
        PINE_INFO("Got control request.");
        Pineapple::Zed::ControlRequest request;
        input_archive(request);
        PINE_INFO("Control request: {0}", request.action);
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::ControlResponse)
    {
        PINE_INFO("Got control response.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::SettingsRequest)
    {
        PINE_INFO("Got settings request.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::SettingsResponse)
    {
        PINE_INFO("Got settings response.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::StateRequest)
    {
        PINE_INFO("Got state request.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::StateResponse)
    {
        PINE_INFO("Got state response.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::SensorRequest)
    {
        PINE_INFO("Got sensor request.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::SensorResponse)
    {
        PINE_INFO("Got sensor response.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::ImageRequest)
    {
        PINE_INFO("Got image request.");
    }
    else if (identifier == Pineapple::Zed::MessageIdentifier::ImageResponse)
    {
        PINE_INFO("Got image response.");
    }
    else
    {
        PINE_INFO("Got invalid message.");
    }
}

int main(int argc, char** argv)
{
    Pine::Log::Init();

    TestControlSerialization();
    TestImageSerialization();
    TestMessageSerialization();
    return 0;
}
