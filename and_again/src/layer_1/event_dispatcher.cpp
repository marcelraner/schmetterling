#include <event_handler.hpp>

#include <logger.hpp>

void EventHandler::registerOnUpdateCallback(std::function<void(void)> callback)
{
    this->on_update_callback = callback;
}

void EventHandler::registerOnRenderCallback(std::function<void(void)> callback)
{
    this->on_render_callback = callback;
}

void EventHandler::loop()
{
    SDL_Event event;
    bool quit = false;

    uint32_t triggerer_event_type = SDL_RegisterEvents(1);

    // codes to differentiate triggerer events
    enum TriggererIdCode : int32_t {
        UpdateTriggerer,
        RenderTriggerer
    };

    // activate all triggerers
    this->update_triggerer.activate(triggerer_event_type, TriggererIdCode::UpdateTriggerer);
    this->render_triggerer.activate(triggerer_event_type, TriggererIdCode::RenderTriggerer);

    // join loop
    while (!quit)
    {
        if (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == triggerer_event_type)
            {
                Logger::debug("Custom event received: {}, {}", event.type, event.user.code);
                if (event.user.code == TriggererIdCode::UpdateTriggerer) {
                    Logger::debug("UpdateTriggerer");
                    //this->on_update_callback();
                }
                else if (event.user.code == TriggererIdCode::RenderTriggerer) {
                    //Logger::debug("RenderTriggerer");
                    this->on_render_callback();
                }
                
            }
            else 
            {
                Logger::debug("Unhandled event: {}", event.type);
            }
        }
    }

    // deactivate all triggerers
    this->update_triggerer.deactivate();
    this->render_triggerer.deactivate();
}