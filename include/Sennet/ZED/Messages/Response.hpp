#pragma once
#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/Messages/Request.hpp"
#include "Sennet/ZED/Parameters/InitParameters.hpp"
#include "Sennet/ZED/Parameters/RecordingParameters.hpp"
#include "Sennet/ZED/Parameters/RuntimeParameters.hpp"

namespace Sennet
{

namespace ZED
{

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
		const RecorderState state,
		const InitParameters initParameters,
		const RecordingParameters recordingParameters,
		const RuntimeParameters runtimeParameters,
		const Image image,
		const std::vector<std::pair<std::string, int>> settings);
	~StateResponse() = default;

	MESSAGE_CLASS_TYPE(ZEDStateResponse);

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
		archive(self.m_RecorderState);
		archive(self.m_InitParameters);
		archive(self.m_RecordingParameters);
		archive(self.m_RuntimeParameters);
		archive(self.m_Image);
		archive(self.m_Settings);
	}

private:
	RecorderState m_RecorderState;
	InitParameters m_InitParameters;
	RecordingParameters m_RecordingParameters;
	RuntimeParameters m_RuntimeParameters;
	Image m_Image;
	std::vector<std::pair<std::string, int>> m_Settings;
};

}
}
