#include <memory>

#include <Pine/Pine.hpp>

#include "pineapple/zed/local_control_layer.hpp"

class LocalController : public Pine::Application
{
public:
    LocalController(const Pine::Application::Specification& specs)
        : Pine::Application(specs)
    {
        PushLayer(new pineapple::LocalControlLayer());
    }

    ~LocalController() {}
};

std::unique_ptr<Pine::Application> Pine::CreateApplication(int argc,
    char** argv)
{
    Pine::Application::Specification specs;
    specs.WorkingDirectory = ".";
    specs.Name = "Local Controller";
    specs.WindowWidth = 1600;
    specs.WindowHeight = 800;
    specs.StartMaximized = true;
    specs.VSync = true;
    specs.Resizable = true;
    specs.EnableImGui = true;
    specs.Fullscreen = true;

    return std::make_unique<LocalController>(specs);
}

int main(int argc, char** argv)
{
    Pine::Log::Init();
    auto app = Pine::CreateApplication(argc, argv);
    app->Run();
    return 0;
}
