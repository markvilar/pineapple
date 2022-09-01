#include <memory>

#include <pine/pine.hpp>

#include "pineapple/zed/remote_control_layer.hpp"

class RemoteController : public pine::Application
{
public:
    RemoteController(const pine::ApplicationSpecs& specs)
        : pine::Application(specs)
    {
        push_layer(new pineapple::RemoteControlLayer());
    }

    ~RemoteController() {}
};

class RemoteControllerFactory : public pine::ApplicationFactory
{
public:
    RemoteControllerFactory(int argc_, char** argv_) : argc(argc_), argv(argv_)
    {
    }

    virtual std::unique_ptr<pine::Application> create_application() override
    {
        pine::ApplicationSpecs specs;
        specs.working_directory = ".";
        specs.name = "Remote Controller";
        specs.window_width = 1600;
        specs.window_height = 800;
        specs.start_maximized = true;
        specs.vsync = true;
        specs.resizable = true;
        specs.enable_gui = true;
        specs.fullscreen = true;

        return std::make_unique<RemoteController>(specs);
    }

private:
    int argc;
    char** argv;
};

int main(int argc, char** argv)
{
    pine::Log::init();
    auto factory = RemoteControllerFactory(argc, argv);
    auto app = factory.create_application();
    app->run();
    return 0;
}
