#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet-ZED/Client.hpp"
#include "Sennet-ZED/Image.hpp"
#include "Sennet-ZED/Settings.hpp"

namespace Sennet { namespace ZED {

class SensorControllerPanel
{
public:
	SensorControllerPanel() = default;
	~SensorControllerPanel() = default;

	void SetClient(const Ref<Client>& client);

	void OnImGuiRender();

	bool HasImage() const { return (bool)m_Image; };

	void UpdateImageTexture();

	Ref<Texture2D> GetImageTexture() const { return m_ImageTexture; }
	Ref<Image<uint8_t>> GetImage() const { return m_Image; }

	void OnSensorControllerAccept(Message<MessageTypes>& message);
	void OnSensorControllerDeny(Message<MessageTypes>& message);

	void OnImage(Message<MessageTypes>& message);
	void OnImageStream(Message<MessageTypes>& message);
	
private:
	Ref<Client> m_Client;
	Ref<Texture2D> m_ImageTexture;
	Ref<Image<uint8_t>> m_Image;

	View m_OptionView = View::Left;
	bool m_OptionImageStream = false;
};

}}
