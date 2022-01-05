#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/RuntimeParameters.hpp"

namespace Pineapple
{

class RuntimeParametersPanel
{
public:
    RuntimeParametersPanel() = default;
    RuntimeParametersPanel(const Pine::Ref<Client>& client);

    void SetClient(const Pine::Ref<Client>& client);

    void OnImGuiRender();

private:
    Pine::Ref<Client> m_Client;
    RuntimeParameters m_Parameters;
};

} // namespace Pineapple
