#pragma once

#include <Sennet/pch.hpp>

#include <sl/Camera.hpp>

#include <Sennet/Sennet.hpp>

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

	// ZED Recorder specific member functions.
	void StartRecord();
	void StopRecord();

	bool IsRunning() const { return m_Running; }
	bool IsRecording() const { return m_Recording; }
	bool IsCameraOpened() const;

	::Sennet::Ref<image> GetImage(const view& view=view::left) const;
	::Sennet::Ref<init_params> GetInitParameters() const;
	::Sennet::Ref<recording_params> GetRecordingParameters() const;
	::Sennet::Ref<runtime_params> GetRuntimeParameters() const;

	::Sennet::Ref<init_params> GetZEDInitParameters() const;
	::Sennet::Ref<recording_params> GetZEDRecordingParameters() const;
	::Sennet::Ref<runtime_params> GetZEDRuntimeParameters() const;

	void SetInitParameters(const ::Sennet::Ref<init_params> init_params);
	void SetRecordingParameters(const ::Sennet::Ref<recording_params> rec_params);
	void SetRuntimeParameters(const ::Sennet::Ref<runtime_params> run_params);

private:
	void ExecutionWorker();
	void RecordLoop();

	void StartExecutionThread();
	void StopExecutionThread();
	void JoinExecutionThread();

private:
	// Sensor members.
	::Sennet::Ref<sl::InitParameters> m_InitParameters;
	::Sennet::Ref<sl::RecordingParameters> m_RecordingParameters;
	::Sennet::Ref<sl::RuntimeParameters> m_RuntimeParameters;
	::Sennet::Scope<sl::Camera> m_Camera;

	// Thread members.
	::Sennet::Scope<std::mutex> m_Mutex;
	::Sennet::Scope<std::thread> m_ExecutionThread;
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
