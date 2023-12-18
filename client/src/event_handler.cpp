#include <event_handler.hpp>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <iostream>

void EventHandler::registerOnQuitCallback(std::function<void(void)> callback)
{
    this->on_quit_callback = callback;
}

void EventHandler::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            on_quit_callback();
            break;
        }
    }

    /*CircularBuffer<int> circular_buffer(3);

    circular_buffer.push(0);*/
}
