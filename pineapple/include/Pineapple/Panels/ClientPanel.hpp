#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/Messages.hpp"

namespace Pineapple
{

class ClientPanel
{
public:
    ClientPanel() = default;
    ClientPanel(const Pine::Ref<Client>& client);

    void SetClient(const Pine::Ref<Client>& client);

    void OnImGuiRender();

    void OnServerPing(Pine::TCP::Message<MessageTypes>& message);
    void OnServerAccept(Pine::TCP::Message<MessageTypes>& message);
    void OnServerDeny(Pine::TCP::Message<MessageTypes>& message);

private:
    Pine::Ref<Client> m_Client;
};

} // namespace Pineapple
