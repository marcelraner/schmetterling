#include <window.hpp>

#include <iostream>
#include <format>

#include <logger.hpp>

Window::Window()
{
    Logger::trace("Window()");

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
    Logger::trace("~Window()");

    SDL_DestroyRenderer(this->sdl_renderer);
    this->sdl_renderer = nullptr;

    SDL_DestroyWindow(this->sdl_window);
    this->sdl_window = nullptr;
}

void Window::clear()
{
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->sdl_renderer);
}

void Window::present()
{
    SDL_RenderPresent(this->sdl_renderer);
}

void Window::draw_rectangle(int32_t x, int32_t y, int32_t h, int32_t w)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(this->sdl_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(this->sdl_renderer, &rect);
}
