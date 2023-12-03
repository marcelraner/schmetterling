#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

class Application
{
private:
    bool sdl_has_been_initialized = false;
    SDL_Window* sdl_window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
public:
    void run();
    void init();
    void mainLoop();
    void cleanup();
};

#endif // APPLICATION_HPP_
