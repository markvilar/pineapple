#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/Image.hpp"
#include "Pineapple/Settings.hpp"

namespace Pineapple
{

class SensorControllerPanel
{
public:
    SensorControllerPanel() = default;
    ~SensorControllerPanel() = default;

    void SetClient(const Pine::Ref<Client>& client);

    void OnImGuiRender();

    bool HasImage() const { return (bool)m_Image; };

    void UpdateImageTexture();

    Pine::Ref<Pine::Texture2D> GetImageTexture() const
    {
        return m_ImageTexture;
    }
    Pine::Ref<Image<uint8_t>> GetImage() const { return m_Image; }

    void OnImage(Pine::TCP::Message<MessageTypes>& message);
    void OnImageDeny(Pine::TCP::Message<MessageTypes>& message);

    void OnImageStream(Pine::TCP::Message<MessageTypes>& message);
    void OnImageStreamDeny(Pine::TCP::Message<MessageTypes>& message);

    void OnSensorControllerAccept(Pine::TCP::Message<MessageTypes>& message);
    void OnSensorControllerDeny(Pine::TCP::Message<MessageTypes>& message);

private:
    Pine::Ref<Client> m_Client;

    Pine::Ref<Pine::Texture2D> m_ImageTexture;
    Pine::Ref<Image<uint8_t>> m_Image;

    View m_OptionView = View::Left;
    bool m_OptionImageStream = false;
};

} // namespace Pineapple
