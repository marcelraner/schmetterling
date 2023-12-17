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
    void clear();
    void present();
    void draw_rectangle(int32_t x, int32_t y, int32_t h, int32_t w);
    void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
private:
    SdlInitializer sdl_initializer;
    SDL_Window *sdl_window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
};

#endif // WINDOW_HPP_
