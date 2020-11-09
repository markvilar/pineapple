#pragma once

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages.hpp"

namespace Sennet { namespace ZED {

class RecordClient : public Sennet::Client<MessageTypes>
{
public:
	RecordClient();
	virtual ~RecordClient();

private:

};

}}
