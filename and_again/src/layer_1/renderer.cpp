#include <renderer.hpp>

#include <logger.hpp>

Renderer::Renderer(Window &window) : window{window}
{
    this->sdl_renderer = SDL_CreateRenderer(this->window.sdl_window,
                                            -1,
                                            SDL_RENDERER_ACCELERATED);
    if (this->sdl_renderer == nullptr)
    {
        std::cerr << "ERROR: SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        throw std::runtime_error(std::format("SDL_Error: {}", SDL_GetError()));
    }
}

void Renderer::clear()
{
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->sdl_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(this->sdl_renderer);
}
