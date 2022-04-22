#include <memory>

#include <Pine/Pine.hpp>

#include "Pineapple/Zed/RemoteControlLayer.hpp"

class RemoteController : public Pine::Application
{
public:
    RemoteController(const Pine::Application::Specification& specs)
        : Pine::Application(specs)
    {
        PushLayer(new Pineapple::RemoteControlLayer());
    }

    ~RemoteController() {}
};

std::unique_ptr<Pine::Application> Pine::CreateApplication(int argc, char** argv)
{
    Pine::Application::Specification specs;
    specs.WorkingDirectory = ".";
    specs.Name = "Remote Controller";
    specs.WindowWidth = 1600;
    specs.WindowHeight = 800;
    specs.StartMaximized = true;
    specs.VSync = true;
    specs.Resizable = true;
    specs.EnableImGui = true;
    specs.Fullscreen = true;

    return std::make_unique<RemoteController>(specs);
}

int main(int argc, char** argv)
{
    Pine::Log::Init();
    auto app = Pine::CreateApplication(argc, argv);
    app->Run();
    return 0;
}
