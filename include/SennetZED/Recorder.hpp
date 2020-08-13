#pragma once

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

#include <SennetZED/Primitives/Settings.hpp>

namespace Sennet
{

namespace ZED
{

class Recorder : public SourceHandle
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

	void Init() override;
	void Shutdown() override;

	SOURCE_HANDLE_CLASS_TYPE(ZEDRecorder);

	std::string ToString() const override;

	// ZED ZEDRecorder specific member functions.
	void StartRecord();
	void StopRecord();

	bool IsRunning() const { return m_Running; }
	bool IsRecording() const { return m_Recording; }
	bool IsCameraOpened() const;

	Ref<Image> GetImage(const View& view = View::Left) const;
	InitParameters GetInitParameters() const;
	RecordingParameters GetRecordingParameters() const;
	RuntimeParameters GetRuntimeParameters() const;

	void SetInitParameters(const InitParameters& initParameters);
	void SetRecordingParameters(const RecordingParameters& recordingParameters);
	void SetRuntimeParameters(const RuntimeParameters& runtimeParameters);

private:
	void ExecutionWorker();
	void RecordLoop();

	void StartExecutionThread();
	void StopExecutionThread();
	void JoinExecutionThread();

private:
	// Sensor members.
	sl::InitParameters m_InitParameters;
	sl::RecordingParameters m_RecordingParameters;
	sl::RuntimeParameters m_RuntimeParameters;
	Scope<sl::Camera> m_Camera;

	// Thread members.
	Scope<std::mutex> m_Mutex;
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
