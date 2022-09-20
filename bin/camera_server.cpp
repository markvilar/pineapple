#include <chrono>
#include <csignal>
#include <filesystem>
#include <thread>

#include <pine/pine.hpp>

#include "pineapple/zed/camera_manager.hpp"

sig_atomic_t interrupted = 0;
void on_interrupt(const int code) { interrupted = 1; }

int main(int argc, char** argv)
{
    // Set up signal handler
    std::signal(SIGINT, &on_interrupt);

    pine::Log::init();

    // Set up camera manager
    const auto port = 6000;
    const std::filesystem::path directory = ".";
    zed::CameraManager manager(port, directory);

    // Start camera manager in separate thread
    auto worker_thread = std::thread([&manager](){ manager.run(); });

    // Run until interrupted
    while (!interrupted)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    PINE_INFO("Stopping server.");
    manager.stop();

    // Clean up worker thread
    if (worker_thread.joinable()) 
        worker_thread.join();
}
