#pragma once

#include <mutex>

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

#include <SennetZED/Primitives/Settings.hpp>

namespace Sennet
{

namespace ZED
{

class Recorder
{
	// Handle for recording with a ZED camera. The ZED camera is operated
	// in a separate execution thread. The handle public member functions
	// interact with the sensor in a thread safe manner. Additionally, all
	// returned data types are POD or Sennet types in order to make the 
	// communication layer independent of the Stereolabs SDK.

public:
	// Source handle member functions.
	Recorder();
	~Recorder();

	// Actions
	void Initialize();
	void Shutdown();
	void StartRecord();
	void StopRecord();

	std::string ToString() const;

	bool IsRunning() const { return m_Running; }
	bool IsRecording() const { return m_Recording; }
	bool IsCameraOpened();

	RecorderState GetState() const;
	Ref<Image> GetImage(const View& view = View::Left);

	std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
		GetParameters();

	std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
		GetParametersCache();

	void SetParametersCache(const InitParameters initParameters,
		const RecordingParameters recordingParameters,
		const RuntimeParameters runtimeParameters);

	

private:
	void ExecutionWorker();
	void RecordLoop();

	void StartExecutionThread();
	void StopExecutionThread();
	void JoinExecutionThread();

private:
	InitParameters m_InitParameters;
	RecordingParameters m_RecordingParameters;
	RuntimeParameters m_RuntimeParameters;

	Scope<sl::Camera> m_Camera;

	std::mutex m_CameraMutex;
	std::mutex m_ParametersMutex;

	Scope<std::thread> m_ExecutionThread;
	std::chrono::milliseconds m_InitTimeout;
	std::chrono::milliseconds m_WorkerTimeout;
	std::chrono::milliseconds m_RecordTimeout;

	// Status flags.
	std::atomic<bool> m_Running;
	std::atomic<bool> m_Recording;

	// Command flags.
	std::atomic<bool> m_ShouldRun;
	std::atomic<bool> m_ShouldRecord;
};

}
}
