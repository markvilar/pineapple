#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include <pine/pine.hpp>

#include "pineapple/message.hpp"

#include "pineapple/zed/protocol.hpp"

void serialize_parameters()
{
    pineapple::Message message;
    zed::CameraParameters parameters;

    PINE_INFO("Resoltion:    {}", parameters.resolution);
    PINE_INFO("Compression:  {}", parameters.compression);
    PINE_INFO("FPS:          {}", parameters.fps);
    PINE_INFO("Timeout:      {}", parameters.timeout);
    PINE_INFO("Image enh.:   {}", parameters.enable_image_enhancement);
    PINE_INFO("Self calib.:  {}", parameters.disable_self_calibration);
    PINE_INFO("Req. sensors: {}", parameters.require_sensors);
    PINE_INFO("Enable depth: {}", parameters.enable_depth);
  
    message.push(parameters.resolution);
    message.push(parameters.compression);
    message.push(parameters.fps);
    message.push(parameters.timeout);
    message.push(parameters.enable_image_enhancement);
    message.push(parameters.disable_self_calibration);
    message.push(parameters.require_sensors);
    message.push(parameters.enable_depth);

    zed::CameraParameters remote;
    remote.resolution = zed::Resolution::HD2K;
    remote.compression = zed::Compression::H265;
    remote.fps = 10;
    remote.enable_depth = true;

    PINE_INFO("------------------------------------");
    PINE_INFO("Resoltion:    {}", remote.resolution);
    PINE_INFO("Compression:  {}", remote.compression);
    PINE_INFO("FPS:          {}", remote.fps);
    PINE_INFO("Timeout:      {}", remote.timeout);
    PINE_INFO("Image enh.:   {}", remote.enable_image_enhancement);
    PINE_INFO("Self calib.:  {}", remote.disable_self_calibration);
    PINE_INFO("Req. sensors: {}", remote.require_sensors);
    PINE_INFO("Enable depth: {}", remote.enable_depth);

    message.pop(remote.enable_depth);
    message.pop(remote.require_sensors);
    message.pop(remote.disable_self_calibration);
    message.pop(remote.enable_image_enhancement);
    message.pop(remote.timeout);
    message.pop(remote.fps);
    message.pop(remote.compression);
    message.pop(remote.resolution);

    PINE_INFO("------------------------------------");
    PINE_INFO("Resoltion:    {}", remote.resolution);
    PINE_INFO("Compression:  {}", remote.compression);
    PINE_INFO("FPS:          {}", remote.fps);
    PINE_INFO("Timeout:      {}", remote.timeout);
    PINE_INFO("Image enh.:   {}", remote.enable_image_enhancement);
    PINE_INFO("Self calib.:  {}", remote.disable_self_calibration);
    PINE_INFO("Req. sensors: {}", remote.require_sensors);
    PINE_INFO("Enable depth: {}", remote.enable_depth);

    PINE_INFO("------------------------------------");
    PINE_INFO("Final message size: {0}", message.size());
}

void serialize_image()
{
    pineapple::Message message;
    zed::Image image;

    PINE_INFO("Width:  {0}", image.specification.width);
    PINE_INFO("Height: {0}", image.specification.height);
    PINE_INFO("View:   {0}", image.specification.view);

    message.push(image.specification.width);
    message.push(image.specification.height);
    message.push(image.specification.view);

    zed::Image remote;
    message.pop(remote.specification.view);
    message.pop(remote.specification.height);
    message.pop(remote.specification.width);

    PINE_INFO("Width:  {0}", remote.specification.width);
    PINE_INFO("Height: {0}", remote.specification.height);
    PINE_INFO("View:   {0}", remote.specification.view);
}

int main(int argc, char** argv)
{
    pine::Log::init();

    bool test_parameters = false;
    bool test_image = true;

    if (test_parameters)
        serialize_parameters();
    if (test_image)
        serialize_image();

    return 0;
}
