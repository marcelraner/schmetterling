#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include "subsysteminitializer.hpp"

#include <functional>

class EventHandler
{
public:
    EventHandler() {}
    void registerOnQuitCallback(std::function<void(void)> callback);
    void handleEvents();
private:
    SdlSubsystemInitializer sdl_subsystem_initializer;
    std::function<void(void)> on_quit_callback;
};

#endif // EVENTHANDLER_HPP_
