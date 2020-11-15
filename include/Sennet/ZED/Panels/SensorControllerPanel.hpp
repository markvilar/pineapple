#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Client.hpp"
#include "Sennet/ZED/Image.hpp"
#include "Sennet/ZED/Settings.hpp"

namespace Sennet { namespace ZED {

class SensorControllerPanel
{
public:
	SensorControllerPanel() = default;
	~SensorControllerPanel() = default;

	void SetClient(const Ref<Client>& client);
	void SetImage(const Ref<Image<uint8_t>>& image);

	void OnImGuiRender();

	void OnSensorControllerAccept(Message<MessageTypes>& message);
	void OnSensorControllerDeny(Message<MessageTypes>& message);
	
private:
	Ref<Client> m_Client;
	Ref<Texture2D> m_ImageTexture;
	Ref<Image<uint8_t>> m_Image;

	View m_OptionView = View::Left;
	bool m_OptionImageStream = false;

	bool m_StatusRecentImage = false;
};

}}
