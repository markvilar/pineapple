#pragma once

#include "Pine/Pine.hpp"

#include "Pineapple/CameraParameters.hpp"
#include "Pineapple/CameraSettings.hpp"
#include "Pineapple/Messages.hpp"

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

    void RequestImage(const ZED::View& view);
    void RequestImageStream(const ZED::View& view);

private:
};

} // namespace Pineapple
