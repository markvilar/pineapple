#pragma once

#include <filesystem>
#include <mutex>
#include <tuple>

#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "sl/Camera.hpp"

#include "Pine/Pine.hpp"

#include "Pineapple/Image.hpp"
#include "Pineapple/InitParameters.hpp"
#include "Pineapple/RecordingParameters.hpp"
#include "Pineapple/RuntimeParameters.hpp"
#include "Pineapple/Settings.hpp"

namespace Pineapple
{

class SensorController
{

public:
    SensorController(const std::string& rootDirectory = "./");
    ~SensorController();

    // Actions
    void Initialize();
    void Shutdown();
    void Start();
    void Stop();

    bool IsRunning() const { return m_Running; }
    bool IsRecording() const { return m_Recording; }
    bool IsCameraOpen();

    Pine::Ref<Image<uint8_t>> GetImage(const View& view = View::Left);

    std::tuple<InitParameters, RecordingParameters, RuntimeParameters>
    GetCurrentCameraParameters();

    InitParameters GetInitParameters();
    RecordingParameters GetRecordingParameters();
    RuntimeParameters GetRuntimeParameters();

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
    InitParameters m_InitParameters;
    RecordingParameters m_RecordingParameters;
    RuntimeParameters m_RuntimeParameters;
    std::string m_RootDirectory;

    sl::Camera m_Camera;

    std::mutex m_CameraMutex;
    std::mutex m_ParametersMutex;

    Pine::Scope<std::thread> m_ExecutionThread;
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

} // namespace Pineapple
