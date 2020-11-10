#pragma once

#include <imgui.h>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"
#include "Sennet/ZED/RecordClient.hpp"

namespace Sennet { namespace ZED {

class RecordClientPanel
{
public:
	RecordClientPanel() = default;
	RecordClientPanel(const Ref<RecordClient>& context);

	void SetContext(const Ref<RecordClient>& context);
	void SetParameters(const Ref<InitParameters>& parameters);
	void SetParameters(const Ref<RecordingParameters>& parameters);
	void SetParameters(const Ref<RuntimeParameters>& parameters);

	void OnImGuiRender();

	void OnServerPing(Message<MessageTypes>& message);

private:
	Ref<RecordClient> m_Context;

	// TODO: Information holders?
};

}}
