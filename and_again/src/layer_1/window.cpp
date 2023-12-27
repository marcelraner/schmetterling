#include <window.hpp>

#include <iostream>
#include <format>

#include <logger.hpp>

Window::Window()
{
    this->sdl_window = SDL_CreateWindow("Sample",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        800, 600,
                                        SDL_WINDOW_RESIZABLE);
    if (this->sdl_window == nullptr)
    {
        Logger::error("Couldn't create SDL window: {}", SDL_GetError());
        throw std::runtime_error(std::format("SDL_Error: {}", SDL_GetError()));
    }
}

Window::~Window()
{
    SDL_DestroyWindow(this->sdl_window);
    this->sdl_window = nullptr;
}

std::tuple<int32_t, int32_t> Window::get_size()
{
    int32_t width = 0;
    int32_t height = 0;
    SDL_GetWindowSize(this->sdl_window, &width, &height);
    return {width, height};
}

