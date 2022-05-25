#include <filesystem>

#include <Pine/Pine.hpp>

#include "pineapple/zed/camera_manager.hpp"

int main(int argc, char** argv)
{
    Pine::Log::Init();

    const auto port = 6000;
    const std::filesystem::path directory = ".";

    Pineapple::Zed::CameraManager manager(port, directory);
    manager.Run();
}
