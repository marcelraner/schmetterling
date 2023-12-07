#include "application.hpp"

#include "window.hpp"
#include "eventhandler.hpp"
#include "inputhandler.hpp"

#include <functional>

void Application::run()
{
    Window window;
    EventHandler event_handler;
    InputHandler input_handler;

    this->application_is_running = true;

    event_handler.registerOnQuitCallback(std::bind(&Application::quit, this));

    while (this->application_is_running) {
        event_handler.handleEvents();
        input_handler.handleInput(); // TODO: must update gamestate or inputstate
    }
}

void Application::quit()
{
    this->application_is_running = false;
}
