#ifndef TRIGGERER_PERIODIC_HPP_
#define TRIGGERER_PERIODIC_HPP_

#include <sdl_initializer.hpp>
#include <interface_triggerer.hpp>
#include <thread>

class PeriodicTriggerer : public ITriggerer
{
public:
    PeriodicTriggerer(std::chrono::nanoseconds period_time_ns) : period_time_ns{period_time_ns} {};
    void activate(uint32_t triggerer_event_type, int32_t triggerer_id_code) {
        this->shutdown = false;
        this->trigger_update_thread = std::thread(&PeriodicTriggerer::trigger_update_thread_func, this, triggerer_event_type, triggerer_id_code);
    }
    void deactivate() {
        this->shutdown = true;
        this->trigger_update_thread.join();
    }
private:
    void trigger_update_thread_func(uint32_t triggerer_event_type, int32_t triggerer_id_code) {
        while (!this->shutdown) {
            std::this_thread::sleep_for(period_time_ns);

            // Create a custom event
            SDL_Event event;
            event.type = triggerer_event_type;
            event.user.code = triggerer_id_code;
            event.user.data1 = nullptr;
            event.user.data2 = nullptr;

            // Push the custom event to the event queue
            SDL_PushEvent(&event);
        }
    }
private:
    SdlInitializer sdl_initializer;
    std::thread trigger_update_thread;
    bool shutdown;
    std::chrono::nanoseconds period_time_ns;
};

#endif // TRIGGERER_PERIODIC_HPP_
