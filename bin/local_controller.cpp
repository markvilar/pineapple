#include <memory>

#include <pine/pine.hpp>

#include "pineapple/zed/local_control_layer.hpp"

class LocalController : public pine::Application
{
public:
    LocalController(const pine::ApplicationSpecs& specs)
        : pine::Application(specs)
    {
        push_layer(new pineapple::LocalControlLayer());
    }

    ~LocalController() {}
};

class LocalControllerFactory : public pine::ApplicationFactory
{
public:
    LocalControllerFactory(int argc_, char** argv_) : argc(argc_), argv(argv_)
    {
    }

    virtual std::unique_ptr<pine::Application> create_application() override
    {
        pine::ApplicationSpecs specs;
        specs.working_directory = ".";
        specs.name = "Local Controller";
        specs.window_width = 1600;
        specs.window_height = 800;
        specs.start_maximized = true;
        specs.vsync = true;
        specs.resizable = true;
        specs.enable_gui = true;
        specs.fullscreen = true;

        return std::make_unique<LocalController>(specs);
    }

private:
    int argc;
    char** argv;
};

int main(int argc, char** argv)
{
    pine::Log::init();
    auto factory = LocalControllerFactory(argc, argv);
    auto app = factory.create_application();
    app->run();
    return 0;
}
