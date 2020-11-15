#include "Sennet/ZED/Panels/SensorControllerPanel.hpp"

namespace Sennet { namespace ZED {

void SensorControllerPanel::SetClient(const Ref<Client>& client)
{
	m_Client = client;
}

void SensorControllerPanel::SetImage(const Ref<Image<uint8_t>>& image)
{
	m_Image = image;
}

void SensorControllerPanel::OnSensorControllerAccept(
	Message<MessageTypes>& message)
{
	SN_CORE_INFO("Sensor Controller Accepted!");
}

void SensorControllerPanel::OnSensorControllerDeny(
	Message<MessageTypes>& message)
{
	SN_CORE_INFO("Sensor Controller Denied!");
}

void SensorControllerPanel::OnImGuiRender()
{
}

}}
