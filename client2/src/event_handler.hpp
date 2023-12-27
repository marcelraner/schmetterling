#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include <sdl_initializer.hpp>
#include <vector>
#include <interface_triggerer.hpp>
#include <functional>

class EventHandler
{
public:
    EventHandler(ITriggerer& update_triggerer, ITriggerer& render_triggerer) : update_triggerer{update_triggerer}, render_triggerer{render_triggerer} {};
    void registerOnUpdateCallback(std::function<void(void)> callback);
    void registerOnRenderCallback(std::function<void(void)> callback);
    void loop();
private:
    SdlInitializer sdl_initializer;
    ITriggerer& update_triggerer;
    ITriggerer& render_triggerer;
    std::function<void(void)> on_update_callback;
    std::function<void(void)> on_render_callback;
};

#endif // EVENTHANDLER_HPP_
