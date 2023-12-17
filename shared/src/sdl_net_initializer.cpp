#include <sdl_net_initializer.hpp>

#include <logger.hpp>

size_t SdlNetInitializer::sdl_net_has_been_initialized = 0;

SdlNetInitializer::SdlNetInitializer()
{
    Logger::trace("SdlNetInitializer()");

    if (this->sdl_net_has_been_initialized == 0) {
        Logger::debug("SDLNet_Init()");
        if (SDLNet_Init() < 0) {
            Logger::error("Couldn't initialize sdl net: {}", SDLNet_GetError());
            throw std::runtime_error(std::format("Couldn't initialize sdl net: {}", SDL_GetError()));
        }
    }
    this->sdl_net_has_been_initialized++;

}

SdlNetInitializer::~SdlNetInitializer()
{
    Logger::trace("~SdlNetInitializer()");

    if (this->sdl_net_has_been_initialized == 1) {
        Logger::debug("SDLNet_Quit()");
        SDLNet_Quit();
    }
    if (this->sdl_net_has_been_initialized > 0) {
        this->sdl_net_has_been_initialized--;
    }
}
