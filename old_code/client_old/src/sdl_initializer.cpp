#include <sdl_initializer.hpp>

#include <logger.hpp>

size_t SdlInitializer::sdl_has_been_initialized = 0;

SdlInitializer::SdlInitializer()
{
    Logger::trace("SdlInitializer()");

    if (this->sdl_has_been_initialized == 0) {
        Logger::debug("SDL_InitSubSystem()");
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        {
            Logger::error("Couldn't initialize sdl: {}", SDL_GetError());
            throw std::runtime_error(std::format("Couldn't initialize sdl: {}", SDL_GetError()));
        }
    }
    this->sdl_has_been_initialized++;

}

SdlInitializer::~SdlInitializer()
{
    Logger::trace("~SdlInitializer()");

    if (this->sdl_has_been_initialized == 1) {
        Logger::debug("SDL_Quit()");
        SDL_Quit();
    }
    if (this->sdl_has_been_initialized > 0) {
        this->sdl_has_been_initialized--;
    }
}
