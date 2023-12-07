#include "subsysteminitializer.hpp"

#include <iostream>
#include <format>

size_t SdlSubsystemInitializer::sdl_has_been_initialized = 0;

SdlSubsystemInitializer::SdlSubsystemInitializer()
{
    std::cout << "TRACE: SdlSubsystemInitializer()" << std::endl;

    if (this->sdl_has_been_initialized == 0) {
        std::cout << "DEBUG: SDL_InitSubSystem()" << std::endl;
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "ERROR: SDL_Init(): " << SDL_GetError() << std::endl;
            throw std::runtime_error(std::format("SDL_Error: {}", SDL_GetError()));
        }
    }
    this->sdl_has_been_initialized++;

}

SdlSubsystemInitializer::~SdlSubsystemInitializer()
{
    std::cout << "TRACE: ~SdlSubsystemInitializer()" << std::endl;

    if (this->sdl_has_been_initialized == 1) {
        std::cout << "DEBUG: SDL_Quit()" << std::endl;
        SDL_Quit();
    }
    if (this->sdl_has_been_initialized > 0) {
        this->sdl_has_been_initialized--;
    }
}
