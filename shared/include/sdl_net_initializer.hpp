#ifndef SDL_NET_INITIALIZER_HPP_
#define SDL_NET_INITIALIZER_HPP_

#include <SDL_net.h>

class SdlNetInitializer
{
public:
    SdlNetInitializer();
    ~SdlNetInitializer();
private:
    static size_t sdl_net_has_been_initialized;
};

#endif // SDL_NET_INITIALIZER_HPP_
