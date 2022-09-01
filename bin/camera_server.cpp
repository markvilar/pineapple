#include <filesystem>

#include <pine/pine.hpp>

#include "pineapple/zed/camera_manager.hpp"

int main(int argc, char** argv)
{
    pine::Log::init();

    const auto port = 6000;
    const std::filesystem::path directory = ".";

    pineapple::zed::CameraManager manager(port, directory);
    manager.run();
}
