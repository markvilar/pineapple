#include <SennetZED/Recorder.hpp>

#include <SennetZED/Primitives/Conversion.hpp>

namespace Sennet
{

namespace ZED
{

Recorder::Recorder()
	: m_InitParameters(),
	m_RecordingParameters(),
	m_RuntimeParameters(),
	m_Camera(CreateScope<sl::Camera>()),
	m_Running(false),
	m_Recording(false),
	m_Mutex(CreateScope<std::mutex>()),
	m_ExecutionThread(),
	m_InitTimeout(100),
	m_WorkerTimeout(100),
	m_RecordTimeout(10)
{
	Init();
}

Recorder::~Recorder()
{
	Shutdown();
}

void Recorder::Init()
{
	if (m_Running)
	{
		SN_CORE_WARN("[Recorder] Already initialized.");
		return;
	}
	else if (not m_Running and m_Recording)
	{
		SN_CORE_ERROR("[Recorder] Critical situation! Forcing\
			shutdown and re-initialization.");
	}
	else if (not m_Running and not m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Starting initialization.");
	}

	StopExecutionThread();
	JoinExecutionThread();
	StartExecutionThread();

	// Sleep a bit to allow the execution thread to start up.
	std::this_thread::sleep_for(m_InitTimeout);
}

void Recorder::Shutdown()
{
	if (not m_Running and not m_Recording)
	{
		SN_CORE_WARN("[Recorder] Already shut down.");
	}
	else if (not m_Running and m_Recording)
	{
		SN_CORE_ERROR("[Recorder] Critical situation! Forcing\
			shutdown.");
	}
	else if (m_Running and not m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Starting shutdown.");
	}

	StopExecutionThread();
	JoinExecutionThread();
}

std::string Recorder::ToString() const
{
	// TODO: Implement.
	return std::string("");
}

void Recorder::StartRecord()
{
	if (not m_Running)
	{
		SN_CORE_TRACE("[Recorder] Not initialized, cannot record.");
	}
	else if (m_Running and m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Already recording.");
		m_ShouldRecord = true;
	}
	else if (m_Running and not m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Starting record.");
		m_ShouldRecord = true;
	}
}

void Recorder::StopRecord()
{
	if (m_Running and not m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Not recording.");
	}
	else if (m_Running and m_Recording)
	{
		SN_CORE_TRACE("[Recorder] Stopping record.");
	}
	m_ShouldRecord = false;
}

bool Recorder::IsCameraOpened() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return m_Camera->isOpened();
}

Ref<Image> Recorder::GetImage(const View& view) const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	if (m_Camera->isOpened())
	{
		auto mat = CreateRef<sl::Mat>();
		m_Camera->retrieveImage(*mat, SennetToStereolabs(view));
		return StereolabsToSennet(mat);
	}
	else
	{
		return nullptr;
	}
}

InitParameters Recorder::GetInitParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_InitParameters);
}

RecordingParameters Recorder::GetRecordingParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_RecordingParameters);
}

RuntimeParameters Recorder::GetRuntimeParameters() const
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	return ::StereolabsToSennet(m_RuntimeParameters);
		
}

void Recorder::SetInitParameters(const InitParameters& init_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_InitParameters = ::SennetToStereolabs(init_params);
}

void Recorder::SetRecordingParameters(const RecordingParameters& rec_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_RecordingParameters = ::SennetToStereolabs(rec_params);
}

void Recorder::SetRuntimeParameters(const RuntimeParameters& run_params)
{
	std::lock_guard<std::mutex> lock(*m_Mutex);
	m_RuntimeParameters = ::SennetToStereolabs(run_params);
}

void Recorder::ExecutionWorker()
{
	m_Running = true;
	SN_CORE_TRACE("[Recorder] Execution worker started.");
	while (m_ShouldRun)
	{
		if (m_ShouldRecord)
		{
			RecordLoop();
		}
		std::this_thread::sleep_for(m_WorkerTimeout);
	}
	SN_CORE_TRACE("[Recorder] Execution worker finished.");
	m_Running = false;
}

void Recorder::RecordLoop()
{
	m_Recording = true;
	SN_CORE_TRACE("[Recorder] Record loop started.");

	m_Mutex->lock();
	auto openError = m_Camera->open(m_InitParameters);
	m_Mutex->unlock();
	if (openError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[Recorder] Could not open ZED!");
	}
	else
	{
		SN_CORE_TRACE("[Recorder] ZED opened.");
	}

	m_Mutex->lock();
	auto recordError = m_Camera->enableRecording(m_RecordingParameters);
	m_Mutex->unlock();
	if (recordError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("[Recorder] ZED couldn't enable recording!");
	}
	else
	{
		SN_CORE_TRACE("[Recorder] ZED recording enabled.");
	}

	sl::ERROR_CODE grabError;
	SN_CORE_TRACE("[Recorder] ZED recording.");
	while (m_ShouldRecord)
	{
		m_Mutex->lock();
		grabError = m_Camera->grab(m_RuntimeParameters);
		m_Mutex->unlock();
		if (grabError != sl::ERROR_CODE::SUCCESS)
		{
			SN_CORE_WARN("[Recorder] ZED grab failed!");
		}

		std::this_thread::sleep_for(m_RecordTimeout);
	}

	m_Mutex->lock();
	m_Camera->close();
	m_Mutex->unlock();

	SN_CORE_TRACE("[Recorder] Record loop finished.");
	m_Recording = false;
}

void Recorder::StartExecutionThread()
{
	m_ShouldRun = true;
	m_ExecutionThread = ::Sennet::CreateScope<std::thread>(
		&Recorder::ExecutionWorker, this);
}

void Recorder::StopExecutionThread()
{
	StopRecord();
	m_ShouldRun = false;
}

void Recorder::JoinExecutionThread()
{
	if (not m_ExecutionThread)
	{
		return;
	}
	else if (m_ExecutionThread->joinable())
	{
		m_ExecutionThread->join();
		SN_CORE_INFO("[Recorder] Joined execution thread.");
	}
}

}
}
