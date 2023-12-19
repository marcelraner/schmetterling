#include <iostream>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <logger.hpp>
#include <thread>

class Application
{
public:
    Application()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error(std::format("Couldn't initialize sdl video: {}", SDL_GetError()));
        }
    }

    ~Application()
    {
        SDL_Quit();
    }

    void run()
    {
        this->custom_event_type = SDL_RegisterEvents(1);

        this->trigger_update_thread_quit = false;
        this->trigger_update_thread = std::thread(&Application::trigger_update_thread_func, this);

        SDL_Event event;
        bool quit = false;
        while (!quit) {
            if (SDL_WaitEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                    trigger_update_thread_quit = true;
                }
                else if (event.type == this->custom_event_type) {
                    std::cout << "Custom event received!" << std::endl;
                }
            }
        }

        this->trigger_update_thread.join();
    }

private:
    void trigger_update_thread_func() {
        while (!trigger_update_thread_quit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            // Create a custom event
            SDL_Event event;
            event.type = this->custom_event_type;
            event.user.data1 = nullptr;
            event.user.data2 = nullptr;

            // Push the custom event to the event queue
            SDL_PushEvent(&event);
        }
    }

private:
    uint32_t custom_event_type;
    std::thread trigger_update_thread;
    bool trigger_update_thread_quit;
}
;

int main()
{
    Logger::info("push_events_sample v0.1");

    Application app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        Logger::exception("{}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}