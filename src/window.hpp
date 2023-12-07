#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "subsysteminitializer.hpp"

class Window
{
public:
    Window();
    ~Window();
private:
    SdlSubsystemInitializer sdl_subsystem_initializer;
    SDL_Window *sdl_window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
};

#endif // WINDOW_HPP_
