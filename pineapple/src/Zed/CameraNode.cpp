#include "Pineapple/Zed/CameraNode.hpp"

#include "Pineapple/Zed/Protocol.hpp"

namespace Pineapple
{

CameraNode::CameraNode(const uint16_t port, 
    const std::filesystem::path& outputDirectory)
    : m_Server(port), m_RecordManager(outputDirectory)
{
}

CameraNode::~CameraNode()
{
    PINE_INFO("Stopping server.");
    StopServer(m_Server);
}

void CameraNode::Run()
{
    Pine::StartServer(m_Server, 
        [this](const Pine::ConnectionState& connection) -> bool
        {
            PINE_INFO("Server got connection: {0}", 
                connection.Socket.remote_endpoint());
            return true;
        });

    while (m_Running)
    {
        OnUpdate();
    }
}

void CameraNode::OnUpdate()
{
    Pine::UpdateServer(m_Server, 
        [this](const Pine::Message& message) -> void
        {
            OnMessage(message);
        });
}

void CameraNode::OnMessage(const Pine::Message& message)
{
    PINE_INFO("Got message: {0}", message.Header.Size);
}

}; // namespace Pineapple
