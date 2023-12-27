#include <client_application.hpp>

#include <logger.hpp>

#include <sdl_initializer.hpp>
#include <window.hpp>
#include <renderer.hpp>

#include <mutex>
#include <condition_variable>

class EventDispatcher
{
public:
    void wait_for_event_and_dispatch()
    {
        std::unique_lock<std::mutex> lock(this->mutex);
        this->cv.wait(lock, [this]
                      { return this->event_triggered; });
        std::cout << "EventDispatcher: Event triggered!" << std::endl;
        this->event_triggered = false;
        // callRegisteredEvents();
    }

    void trigger_event()
    {
        std::lock_guard<std::mutex> lock(this->mutex);
        this->event_triggered = true;
        this->cv.notify_one();
    }

private:
    std::mutex mutex;
    bool event_triggered;
    std::condition_variable cv;
};

class EventTrigger
{
public:
    EventTrigger(EventDispatcher &event_dispatcher) : event_dispatcher(event_dispatcher)
    {
        this->shutdown = false;
        this->trigger_thread = std::thread(&EventTrigger::trigger_thread_func, this);
    }
    ~EventTrigger()
    {
        this->shutdown = true;
        this->trigger_thread.join();
    }

private:
    void trigger_thread_func()
    {
        while (!this->shutdown)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "EventTrigger: Triggering event ..." << std::endl;
            this->event_dispatcher.trigger_event();
        }
    }

private:
    EventDispatcher &event_dispatcher;
    bool shutdown;
    std::thread trigger_thread;
};

class DummyUpdater {
public:
    void update() {

    }
};

class DummyRenderer {
    void render() {

    }
}

class DummySdlEventHandler {
    
}

void ClientApplication::run()
{
    Logger::trace("ClientApplication::run()");

    // SdlInitializer sdl_initializer;
    // Window window;
    // Renderer renderer(window);
    /*SdlEventDispatcher event_dispatcher(sdl_initializer);
    SdlWindow window(sdl_initializer);
    SdlRenderer renderer(window);


    // How to connect events with actions
    event_dispatcher.subscribe(eventType, listener);


    bool running = true;

    while (running) {
        event_dispatcher.wait_and_dispatch();
    }*/

    EventDispatcher event_dispatcher;

    // update event trigger
    EventTrigger update_event_trigger(event_dispatcher);

    // render event trigger
    EventTrigger render_event_trigger(event_dispatcher);

    for (;;)
    {
        event_dispatcher.wait_for_event_and_dispatch();
        std::cout << "ClientApplication::run: Looping ..." << std::endl;
    }
}
