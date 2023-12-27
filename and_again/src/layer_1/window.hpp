#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#define SDL_MAIN_HANDLED

#include <SDL.h>

#include <sdl_initializer.hpp>
#include <tuple>

class Window
{
public:
    Window();
    ~Window();
    std::tuple<int32_t, int32_t> get_size();
private:
    SdlInitializer sdl_initializer;
    SDL_Window *sdl_window = nullptr;

    friend class Renderer;
};

#endif // WINDOW_HPP_