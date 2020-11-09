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
	void OnImGuiRender();

private:
	Ref<RecordClient> m_Context;
};

}}
