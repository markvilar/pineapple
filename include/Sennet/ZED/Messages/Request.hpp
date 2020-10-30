#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Parameters/InitParameters.hpp"
#include "Sennet/ZED/Parameters/RecordingParameters.hpp"
#include "Sennet/ZED/Parameters/RuntimeParameters.hpp"

namespace Sennet
{

namespace ZED
{

enum class Command
{
	None 		= 0,
	Initialize 	= 1,
	Shutdown 	= 2,
	StartRecord 	= 3,
	StopRecord 	= 4
};

class CommandRequest : public Request
{
public:
	CommandRequest() = default;
	CommandRequest(const std::string address, const unsigned int port,
		const Command command)
		: Request(address, port), m_Command(command) {}
	virtual ~CommandRequest() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandRequest);

	virtual std::string ToString() const override { return GetName(); }

	const Command GetCommand() const { return m_Command; }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
		archive(self.m_Command);
	}

private:
	Command m_Command;
};

class SettingsRequest : public Request
{
public:
	SettingsRequest() = default;
	SettingsRequest(const std::string address, 
		const unsigned int port,
		const InitParameters& initParameters,
		const RecordingParameters& recordingParameters,
		const RuntimeParameters& runtimeParameters);
	~SettingsRequest() = default;
	
	MESSAGE_CLASS_TYPE(ZEDSettingsRequest);

	InitParameters GetInitParameters() const { return m_InitParameters; }

	RecordingParameters GetRecordingParameters() const 
	{ 
		return m_RecordingParameters; 
	}

	RuntimeParameters GetRuntimeParameters() const 
	{ 
		return m_RuntimeParameters; 
	}

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
		archive(self.m_InitParameters);
		archive(self.m_RecordingParameters);
		archive(self.m_RuntimeParameters);
	}

private:
	InitParameters m_InitParameters;
	RecordingParameters m_RecordingParameters;
	RuntimeParameters m_RuntimeParameters;
};

class StateRequest : public Request
{
public:
	StateRequest() = default;
	StateRequest(const std::string address, const unsigned int port)
		: Request(address, port) {}
	~StateRequest() = default;

	MESSAGE_CLASS_TYPE(ZEDStateRequest);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Request::serialize(archive, self);
	}

private:
};

}
}
