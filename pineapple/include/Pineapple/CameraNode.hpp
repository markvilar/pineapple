#pragma once

#include <cstdint>
#include <filesystem>

#include <Pine/Pine.hpp>

#include "Pineapple/RecordManager.hpp"

namespace Pineapple
{

class CameraNode
{
public:
    CameraNode(const uint16_t port, 
        const std::filesystem::path& outputDirectory = ".");
    ~CameraNode();

    void Run();

private:
    void OnUpdate();
    void OnMessage(const Pine::Message& message);

private:
    bool m_Running = true;

    Pine::ServerState m_Server;
    
    ZED::RecordManager m_RecordManager;
};

}; // namespace Pineapple
