#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#define SDL_MAIN_HANDLED

#include <SDL.h>

#include <sdl_initializer.hpp>

class Window
{
public:
    Window();
    ~Window();
private:
    SdlInitializer sdl_initializer;
    SDL_Window *sdl_window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
};

#endif // WINDOW_HPP_