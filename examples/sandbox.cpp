#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <Pine/Pine.hpp>

#include "pineapple/zed/protocol.hpp"
#include "pineapple/zed/types.hpp"

#include "pineapple/message.hpp"
#include "pineapple/serialization.hpp"

void test_image_serialization()
{
    std::vector<std::uint8_t> buffer;
    zpp::serializer::memory_output_archive output_archive(buffer);
    zpp::serializer::memory_input_archive input_archive(buffer);

    PINE_INFO("---------- Test image serialization ----------");

    // Serialization
    const auto width = 32;
    const auto height = 32;
    const auto channels = 4;
    pineapple::zed::Image output_image;
    output_image.specification.width = width;
    output_image.specification.height = height;
    output_image.specification.view = pineapple::zed::View::LEFT;
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
    pineapple::zed::Image input_image;
    input_archive(input_image);
    PINE_INFO("Input image: {0}, {1}, {2}, {3}\n", 
        input_image.specification.width, 
        input_image.specification.height,
        input_image.specification.view,
        input_image.buffer.size());
}

void test_message_serialization()
{
    std::vector<std::uint8_t> request_buffer;
    zpp::serializer::memory_output_archive 
        request_output_archive(request_buffer);

    PINE_INFO("---------- Test message serialization ----------");

    pineapple::Message<pineapple::zed::MessageIdentifier, 
        pineapple::zed::ControlRequest> control_request_message;
    control_request_message.header 
        = pineapple::zed::MessageIdentifier::ControlRequest;
    control_request_message.body.action 
        = pineapple::zed::CameraAction::START_RECORD;

    request_output_archive(control_request_message);

    PINE_INFO("Serialized control request: {0}", request_buffer.size());

    pineapple::zed::MessageIdentifier identifier;
    zpp::serializer::memory_input_archive input_archive(request_buffer);
    input_archive(identifier);
    PINE_INFO("Deserialized identifier: {0}", identifier);

    if (identifier == pineapple::zed::MessageIdentifier::Unknown)
    {
        PINE_INFO("Got unknown message.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::ControlRequest)
    {
        PINE_INFO("Got control request.");
        pineapple::zed::ControlRequest request;
        input_archive(request);
        PINE_INFO("Control request: {0}", request.action);
    }
    else if (identifier == pineapple::zed::MessageIdentifier::ControlResponse)
    {
        PINE_INFO("Got control response.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::SettingsRequest)
    {
        PINE_INFO("Got settings request.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::SettingsResponse)
    {
        PINE_INFO("Got settings response.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::StateRequest)
    {
        PINE_INFO("Got state request.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::StateResponse)
    {
        PINE_INFO("Got state response.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::SensorRequest)
    {
        PINE_INFO("Got sensor request.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::SensorResponse)
    {
        PINE_INFO("Got sensor response.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::ImageRequest)
    {
        PINE_INFO("Got image request.");
    }
    else if (identifier == pineapple::zed::MessageIdentifier::ImageResponse)
    {
        PINE_INFO("Got image response.");
    }
    else
    {
        PINE_INFO("Got invalid message.");
    }
}

void test_memory_archive()
{
    using ControlRequestMessage 
        = pineapple::Message<pineapple::zed::MessageIdentifier, 
            pineapple::zed::ControlRequest>;

    PINE_INFO("---------- Test memory archive ----------");

    pineapple::MemoryOutputArchive output_archive;

    ControlRequestMessage message;
    message.header = pineapple::zed::MessageIdentifier::ControlRequest;
    message.body.action = pineapple::zed::CameraAction::STOP_RECORD;
    output_archive.serialize(message);

    ControlRequestMessage reply;
    pineapple::MemoryInputArchive input_archive(output_archive.get_buffer());
    input_archive.deserialize(reply);

    PINE_INFO("Message: {0}, {1}", message.header, message.body.action);
    PINE_INFO("Reply:   {0}, {1}", reply.header, reply.body.action);
}

void test_memory_view_archive()
{
    PINE_INFO("---------- Test memory view archive ----------");

    using ControlRequestMessage 
        = pineapple::Message<pineapple::zed::MessageIdentifier, 
            pineapple::zed::ControlRequest>;

    std::vector<uint8_t> buffer(100);

    pineapple::MemoryViewOutputArchive output_archive(buffer.data(),
        buffer.size());
    
    ControlRequestMessage message;
    message.header = pineapple::zed::MessageIdentifier::ControlRequest;
    message.body.action = pineapple::zed::CameraAction::START_RECORD;
    output_archive.serialize(message);

    ControlRequestMessage reply;
    pineapple::MemoryViewInputArchive input_archive(buffer.data(), 
        buffer.size());
    input_archive.deserialize(reply);

    PINE_INFO("Message: {0}, {1}", message.header, message.body.action);
    PINE_INFO("Reply:   {0}, {1}", reply.header, reply.body.action);
}

int main(int argc, char** argv)
{
    Pine::Log::Init();

    test_image_serialization();
    test_message_serialization();

    test_memory_archive();
    test_memory_view_archive();

    return 0;
}
