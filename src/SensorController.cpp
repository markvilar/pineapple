#include "Sennet-ZED/SensorController.hpp"

#include "Sennet-ZED/Conversion.hpp"

#include <ctime>

const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

namespace Sennet
{

namespace ZED
{

SensorController::SensorController(const std::string& rootDirectory)
	: m_InitParameters(), m_RecordingParameters(), m_RuntimeParameters(),
	m_Camera(), m_Running(false), m_Recording(false), m_CameraMutex(),
	m_ParametersMutex(), m_ExecutionThread(), m_InitTimeout(100), 
	m_WorkerTimeout(100), m_RecordTimeout(10)
{
	SN_CORE_ASSERT(std::filesystem::exists(std::filesystem::path(
		rootDirectory)), "SensorController root directory does not exist.");
	SN_CORE_ASSERT(rootDirectory.back() == '/',
		"SensorController root directory must end with '/'.");
	m_RootDirectory = rootDirectory;
	m_RecordingParameters.filename = rootDirectory 
		+ m_RecordingParameters.filename;
}

SensorController::~SensorController()
{
	Shutdown();
}

void SensorController::Initialize()
{
	StopExecutionThread();
	JoinExecutionThread();
	StartExecutionThread();

	// Sleep a bit to allow the execution thread to start up.
	std::this_thread::sleep_for(m_InitTimeout);
}

void SensorController::Shutdown()
{
	StopExecutionThread();
	JoinExecutionThread();
}

void SensorController::Start()
{
	if (m_Running and not m_Recording)
	{
		m_ShouldRecord = true;
	}
}

void SensorController::Stop()
{
	m_ShouldRecord = false;
}

bool SensorController::IsCameraOpen()
{
	std::lock_guard<std::mutex> lock(m_CameraMutex);	
	return m_Camera.isOpened();
}

Ref<Image<uint8_t>> SensorController::GetImage(const View& view)
{
	std::lock_guard<std::mutex> lock(m_CameraMutex);
	if (m_Camera.isOpened())
	{
		// Retrieve image on CPU.
		auto mat = CreateRef<sl::Mat>();
		m_Camera.retrieveImage(*mat, SennetToStereolabs(view));
		return CreateRef<Image<uint8_t>>(mat->getPtr<uint8_t>(),
			mat->getWidth(), mat->getHeight(), mat->getChannels());
	}
	else
	{
		// Return empty image.
		return CreateRef<Image<uint8_t>>();
	}
}

std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
	SensorController::GetCurrentCameraParameters()
{
	std::scoped_lock lock(m_CameraMutex);
	auto initParameters = StereolabsToSennet(m_Camera.getInitParameters());
	auto recordingParameters = StereolabsToSennet(
		m_Camera.getRecordingParameters());
	auto runtimeParameters = StereolabsToSennet(
		m_Camera.getRuntimeParameters());
	return { initParameters, recordingParameters, runtimeParameters };
}

InitParameters SensorController::GetInitParameters()
{
	std::scoped_lock lock(m_ParametersMutex);
	return m_InitParameters;
}

RecordingParameters SensorController::GetRecordingParameters()
{
	std::scoped_lock lock(m_ParametersMutex);
	return m_RecordingParameters;
}

RuntimeParameters SensorController::GetRuntimeParameters()
{
	std::scoped_lock lock(m_ParametersMutex);
	return m_RuntimeParameters;
}

void SensorController::SetInitParameters(const InitParameters& initParameters)
{
	std::scoped_lock lock(m_ParametersMutex);
	m_InitParameters = initParameters;
}

void SensorController::SetRecordingParameters(
	const RecordingParameters& recordingParameters)
{
	std::scoped_lock lock(m_ParametersMutex);
	m_RecordingParameters = recordingParameters;
	m_RecordingParameters.filename = m_RootDirectory 
		+ m_RecordingParameters.filename;
}

void SensorController::SetRuntimeParameters(
	const RuntimeParameters& runtimeParameters)
{
	std::scoped_lock lock(m_ParametersMutex);
	m_RuntimeParameters = runtimeParameters;
}

void SensorController::ExecutionWorker()
{
	m_Running = true;
	while (m_ShouldRun)
	{
		if (m_ShouldRecord)
		{
			RecordLoop();
		}
		std::this_thread::sleep_for(m_WorkerTimeout);
	}
	m_Running = false;
}

void SensorController::RecordLoop()
{
	m_Recording = true;

	// Get parameters from parameter cache.
	m_ParametersMutex.lock();

	// Set filename to current date and time.
	const std::string date = currentDateTime();
	m_RecordingParameters.filename = m_RootDirectory + date + ".svo";
	SN_INFO("{0}", m_RecordingParameters.filename);
	auto initParameters = SennetToStereolabs(m_InitParameters);
	auto recordingParameters = SennetToStereolabs(m_RecordingParameters);
	auto runtimeParameters = SennetToStereolabs(m_RuntimeParameters);
	m_ParametersMutex.unlock();

	m_CameraMutex.lock();
	auto openError = m_Camera.open(initParameters);
	m_CameraMutex.unlock();
	if (openError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("ZED Open Error: {0}", toString(openError).get());
		m_ShouldRecord = false;
		m_Recording = false;
		return;
	}

	m_CameraMutex.lock();
	auto recordError = m_Camera.enableRecording(recordingParameters);
	m_CameraMutex.unlock();
	if (recordError != sl::ERROR_CODE::SUCCESS)
	{
		SN_CORE_WARN("ZED Enable Record Error: {0}", 
			toString(recordError).get());
		m_ShouldRecord = false;
		m_Recording = false;
		return;
	}

	sl::ERROR_CODE grabError;
	while (m_ShouldRecord)
	{
		m_CameraMutex.lock();
		grabError = m_Camera.grab(runtimeParameters);
		m_CameraMutex.unlock();
		if (grabError != sl::ERROR_CODE::SUCCESS)
		{
			SN_CORE_WARN("SensorController could not grab ZED data!");
		}

		std::this_thread::sleep_for(m_RecordTimeout);
	}

	m_CameraMutex.lock();
	if (m_Camera.isOpened())
	{
		m_Camera.close();
	}
	m_CameraMutex.unlock();

	m_Recording = false;
}

void SensorController::StartExecutionThread()
{
	m_ShouldRun = true;
	m_ExecutionThread = ::Sennet::CreateScope<std::thread>(
		&SensorController::ExecutionWorker, this);
}

void SensorController::StopExecutionThread()
{
	Stop();
	m_ShouldRun = false;
}

void SensorController::JoinExecutionThread()
{
	if (not m_ExecutionThread)
	{
		return;
	}
	else if (m_ExecutionThread->joinable())
	{
		m_ExecutionThread->join();
	}
}

}}
