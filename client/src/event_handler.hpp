#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <sdl_initializer.hpp>

#include <functional>

class EventHandler
{
public:
    void registerOnQuitCallback(std::function<void(void)> callback);
    void handleEvents();
private:
    SdlInitializer sdl_initializer;
    std::function<void(void)> on_quit_callback;
};

#endif // EVENTHANDLER_HPP_
