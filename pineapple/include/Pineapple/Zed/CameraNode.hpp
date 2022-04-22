#pragma once

#include <cstdint>
#include <filesystem>

#include <Pine/Pine.hpp>

#include "Pineapple/Zed/RecordManager.hpp"

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
    
    Zed::RecordManager m_RecordManager;
};

}; // namespace Pineapple
