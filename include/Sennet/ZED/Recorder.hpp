#pragma once
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <filesystem>
#include <mutex>
#include <tuple>

#include <sl/Camera.hpp>

#include "Sennet/Sennet.hpp"

#include "Sennet/ZED/InitParameters.hpp"
#include "Sennet/ZED/RecordingParameters.hpp"
#include "Sennet/ZED/RuntimeParameters.hpp"
#include "Sennet/ZED/Settings.hpp"

namespace Sennet { namespace ZED {

class Recorder
{
	// Handle for recording with a ZED camera. The ZED camera is operated
	// in a separate execution thread. The handle public member functions
	// interact with the sensor in a thread safe manner. Additionally, all
	// returned data types are POD or Sennet types in order to make the 
	// communication layer independent of the Stereolabs SDK.

public:
	// Source handle member functions.
	Recorder(const std::string& rootDirectory = std::string(""));
	~Recorder();

	// Actions
	void Initialize();
	void Shutdown();
	void StartRecord();
	void StopRecord();

	bool IsRunning() const { return m_Running; }
	bool IsRecording() const { return m_Recording; }
	bool IsCameraOpen();

	Ref<Image> GetImage(const View& view = View::Left);

	std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
		GetCurrentCameraParameters();

	InitParameters GetInitParameters();
	RecordingParameters GetRecordingParameters();
	RuntimeParameters GetRuntimeParameters();

	void SetInitParameters(const InitParameters& initParameters);
	void SetRecordingParameters(
		const RecordingParameters& recordingParameters);
	void SetRuntimeParameters(const RuntimeParameters& runtimeParameters);

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
	std::string m_RootDirectory;

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

}}
