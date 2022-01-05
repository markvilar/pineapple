#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/Client.hpp"
#include "Pineapple/RecordingParameters.hpp"

namespace Pineapple
{

class RecordingParametersPanel
{
public:
    RecordingParametersPanel() = default;
    RecordingParametersPanel(const Pine::Ref<Client>& client);

    void SetClient(const Pine::Ref<Client>& client);

    void OnImGuiRender();

private:
    Pine::Ref<Client> m_Client;
    RecordingParameters m_Parameters;
};

} // namespace Pineapple
