#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/InitParameters.hpp"
#include "Pineapple/Messages.hpp"
#include "Pineapple/RecordingParameters.hpp"
#include "Pineapple/RuntimeParameters.hpp"
#include "Pineapple/Settings.hpp"

namespace Pineapple
{

class Client : public Pine::TCP::Client<MessageTypes>
{
public:
    Client();
    virtual ~Client();

    void RequestServerPing();

    void RequestSensorControllerInitialization();
    void RequestSensorControllerShutdown();
    void RequestSensorControllerStart();
    void RequestSensorControllerStop();

    void RequestImage(const View& view);
    void RequestImageStream(const View& view);

    void RequestInitParametersUpdate(const InitParameters& parameters);
    void RequestRecordingParametersUpdate(
        const RecordingParameters& parameters);
    void RequestRuntimeParametersUpdate(const RuntimeParameters& parameters);

private:
};

} // namespace Pineapple
