#ifndef SDL_INITIALIZER_HPP_
#define SDL_INITIALIZER_HPP_

#define SDL_MAIN_HANDLED
#include <SDL.h>

class SdlInitializer
{
public:
    SdlInitializer();
    ~SdlInitializer();
private:
    static size_t sdl_has_been_initialized;
};

#endif // SDL_INITIALIZER_HPP_
