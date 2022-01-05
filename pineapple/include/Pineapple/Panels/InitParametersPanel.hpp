#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/InitParameters.hpp"

namespace Pineapple
{

class InitParametersPanel
{
public:
    InitParametersPanel() = default;
    ~InitParametersPanel() = default;

    void SetClient(const Pine::Ref<Client>& client) { m_Client = client; }

    void OnImGuiRender();

private:
    Pine::Ref<Client> m_Client;
    InitParameters m_Parameters;
};

} // namespace Pineapple
