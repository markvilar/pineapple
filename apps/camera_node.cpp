#include <filesystem>

#include <Pine/Pine.hpp>

#include "Pineapple/CameraNode.hpp"

int main(int argc, char** argv)
{
    Pine::Log::Init();

    const auto port = 6000;
    const std::filesystem::path directory = ".";

    Pineapple::CameraNode node(port, directory);
    node.Run();
}
