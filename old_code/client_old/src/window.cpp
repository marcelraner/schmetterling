#include "window.hpp"

#include <iostream>
#include <format>

Window::Window()
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    this->sdl_window = SDL_CreateWindow("Sample",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        800, 600,
                                        SDL_WINDOW_RESIZABLE);
    if (this->sdl_window == nullptr)
    {
        std::cerr << "ERROR: SDL_CreateWindow(): " << SDL_GetError() << std::endl;
        throw std::runtime_error(std::format("SDL_Error: {}", SDL_GetError()));
    }

    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window,
                                            -1,
                                            SDL_RENDERER_ACCELERATED);
    if (this->sdl_renderer == nullptr)
    {
        SDL_DestroyWindow(this->sdl_window);
        this->sdl_window = nullptr;
        std::cerr << "ERROR: SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        throw std::runtime_error(std::format("SDL_Error: {}", SDL_GetError()));
    }
}

Window::~Window()
{
    SDL_DestroyRenderer(this->sdl_renderer);
    this->sdl_renderer = nullptr;

    SDL_DestroyWindow(this->sdl_window);
    this->sdl_window = nullptr;

    SDL_Quit();
}