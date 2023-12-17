#ifndef SUBSYSTEMINITIALIZER_HPP_
#define SUBSYSTEMINITIALIZER_HPP_

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

class SdlSubsystemInitializer
{
public:
    SdlSubsystemInitializer();
    ~SdlSubsystemInitializer();
private:
    static size_t sdl_has_been_initialized;
};

#endif // SUBSYSTEMINITIALIZER_HPP_
