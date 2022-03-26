#include "Pineapple/CameraNode.hpp"

#include "Pineapple/Messages.hpp"

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
    const auto type = static_cast<MessageType>(message.Body[0]);
    PINE_INFO("Got message: {0} : {1}", type, message.Header.Size);
    if (type == MessageType::CameraStartRequest)
    {
        PINE_INFO("CameraStartRequest");
        CameraStartRequest request;
        std::memcpy(&request, &message.Body, sizeof(CameraStartRequest));

        PINE_INFO("Resolution: {0}", request.Parameters.CameraResolution);
        PINE_INFO("FPS:        {0}", request.Parameters.CameraFPS);
        PINE_INFO("Timeout:    {0}", request.Parameters.OpenTimeout);
        PINE_INFO("Enhance.:   {0}", request.Parameters.EnableImageEnhancement);
        PINE_INFO("Calib.:     {0}", request.Parameters.DisableSelfCalibration);
        PINE_INFO("Sensors:    {0}", request.Parameters.RequireSensors);
        PINE_INFO("Compress.:  {0}", request.Parameters.Compression);
        PINE_INFO("Depth:      {0}", request.Parameters.EnableDepth);
    }
}

}; // namespace Pineapple
