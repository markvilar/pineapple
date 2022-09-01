#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <pine/pine.hpp>

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
    output_image.buffer = [width, height, channels]()
    {
        std::vector<uint8_t> v(width * height * channels, 0);
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

void test_memory_archive()
{
    PINE_INFO("---------- Test memory archive ----------");

    pineapple::MemoryOutputArchive output_archive;

    pineapple::zed::ControlService::Request message;
    message.header = pineapple::zed::ServiceIdentifier::CONTROL_REQUEST;
    message.data.action = pineapple::zed::CameraAction::STOP_RECORD;
    output_archive.serialize(message);

    pineapple::zed::ControlService::Request reply;
    pineapple::MemoryInputArchive input_archive(output_archive.get_buffer());
    input_archive.deserialize(reply);

    PINE_INFO("Message: {0}, {1}", message.header, message.data.action);
    PINE_INFO("Reply:   {0}, {1}", reply.header, reply.data.action);

    /*
    if (identifier == pineapple::zed::ServiceIdentifier::UNKNOWN)
    {
        PINE_INFO("Got unknown message.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::CONTROL_REQUEST)
    {
        PINE_INFO("Got control request.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::CONTROL_RESPONSE)
    {
        PINE_INFO("Got control response.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::SETTINGS_REQUEST)
    {
        PINE_INFO("Got settings request.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::SETTINGS_RESPONSE)
    {
        PINE_INFO("Got settings response.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::STATE_REQUEST)
    {
        PINE_INFO("Got state request.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::STATE_RESPONSE)
    {
        PINE_INFO("Got state response.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::SENSOR_REQUEST)
    {
        PINE_INFO("Got sensor request.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::SENSOR_RESPONSE)
    {
        PINE_INFO("Got sensor response.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::IMAGE_REQUEST)
    {
        PINE_INFO("Got image request.");
    }
    else if (identifier == pineapple::zed::ServiceIdentifier::IMAGE_RESPONSE)
    {
        PINE_INFO("Got image response.");
    }
    else
    {
        PINE_INFO("Got invalid message.");
    }
    */
}

void test_memory_view_archive()
{
    PINE_INFO("---------- Test memory view archive ----------");

    std::vector<uint8_t> buffer(100);

    pineapple::MemoryViewOutputArchive output_archive(buffer.data(),
        buffer.size());

    pineapple::zed::ControlService::Request message;
    message.header = pineapple::zed::ServiceIdentifier::CONTROL_REQUEST;
    message.data.action = pineapple::zed::CameraAction::STOP_RECORD;
    output_archive.serialize(message);

    pineapple::zed::ControlService::Request reply;
    pineapple::MemoryViewInputArchive input_archive(buffer.data(),
        buffer.size());
    input_archive.deserialize(reply);

    PINE_INFO("Message: {0}, {1}", message.header, message.data.action);
    PINE_INFO("Reply:   {0}, {1}", reply.header, reply.data.action);
}

int main(int argc, char** argv)
{
    pine::Log::init();

    test_image_serialization();
    test_memory_archive();
    test_memory_view_archive();

    return 0;
}
