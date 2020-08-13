#pragma once
#include <Sennet/Sennet.hpp>

#include <SennetZED/Primitives/Settings.hpp>

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

enum class CommandFeedback
{
	None 			= 0,
	InitializeSuccess 	= 1,
	ShutdownSuccess 	= 2,
	StartRecordSuccess 	= 3,
	StopRecordSuccess 	= 4,
	InitializeFailure	= 5,
	ShutdownFailure		= 6,
	StartRecordFailure	= 7,
	StopRecordFailure	= 8
};

class CommandResponse: public Response
{
public:
	CommandResponse() = default;
	CommandResponse(const std::string address, const unsigned int port,
		const Command command,
		const CommandFeedback feedback)
		: Response(address, port), m_Command(command), 
		m_CommandFeedback(feedback) {}
	~CommandResponse() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandResponse);

	CommandFeedback GetFeedback() const { return m_CommandFeedback; }

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_CommandFeedback);
	}

private:
	Command	m_Command;
	CommandFeedback m_CommandFeedback;
};

enum class SettingsFeedback
{
	None 	= 0,
	Success = 1,
	Failure = 2
};

class SettingsResponse : public Response
{
public:
	SettingsResponse() = default;
	SettingsResponse(const std::string address, const unsigned int port,
		const SettingsFeedback feedback)
		: Response(address, port), m_SettingsFeedback(feedback) {}
	~SettingsResponse() = default;
	
	MESSAGE_CLASS_TYPE(ZEDSettingsResponse);

	virtual std::string ToString() const override { return GetName(); }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_SettingsFeedback);
	}

private:
	SettingsFeedback m_SettingsFeedback;
};

class StateResponse: public Response
{
public:
	StateResponse() = default;
	StateResponse(const std::string address, 
		const unsigned int port,
		const InitParameters initParameters,
		const RecordingParameters recordingParameters,
		const RuntimeParameters runtimeParameters,
		const Image& image);
	~StateResponse() = default;

	MESSAGE_CLASS_TYPE(ZEDCommandResponse);

	virtual std::string ToString() const override { return GetName(); }

	InitParameters GetInitParameters() const
	{
		return m_InitParameters;
	}

	RecordingParameters GetRecordingParameters() const
	{
		return m_RecordingParameters;
	}

	RuntimeParameters GetRuntimeParameters() const
	{
		return m_RuntimeParameters;
	}

	Image GetImage() const { return m_Image; }

	friend zpp::serializer::access;
	template <typename Archive, typename Self>
	static void serialize(Archive& archive, Self& self)
	{
		Response::serialize(archive, self);
		archive(self.m_InitParameters);
		archive(self.m_RecordingParameters);
		archive(self.m_RuntimeParameters);
		archive(self.m_Image);
	}

private:
	InitParameters m_InitParameters;
	RecordingParameters m_RecordingParameters;
	RuntimeParameters m_RuntimeParameters;
	Image m_Image;
};

}
}
