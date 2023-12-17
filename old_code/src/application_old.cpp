#include "application.hpp"

#include <iostream>
#include <chrono>
#include <thread>

void Application::mainLoop()
{
    std::cout << "TRACE: Application::mainLoop()" << std::endl;

    bool game_is_still_running = true;

    int player_position_x = 800 / 2;
    int player_position_y = 600 / 2;

    int64_t update_accumulator_us = 0;
    int64_t update_interval_us = 2000;
    int64_t render_accumulator_us = 0;
    int64_t render_interval_us = 16666;

    auto time_now = std::chrono::system_clock::now();
    auto time_last = time_now;

    while (game_is_still_running)
    {
        bool update = false;
        bool render = false;
        SDL_Event event;
        const Uint8* currentKeyStates;

        // get time and update delta
        time_last = time_now;
        time_now = std::chrono::system_clock::now();
        auto time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time_now - time_last).count();
        //std::cout << "DEBUG: time_delta: " << time_delta << std::endl;
        update_accumulator_us += time_delta;
        render_accumulator_us += time_delta;
        if (update_accumulator_us >= update_interval_us) {
            update_accumulator_us -= update_interval_us;
            update = true;
        }
        if (render_accumulator_us >= render_interval_us) {
            render_accumulator_us -= render_interval_us;
            render = true;
        }

        // poll events
        while (SDL_PollEvent(&event))
        { // poll until all events are handled!
            // decide what to do with this event.
            switch (event.type)
            {
            case SDL_QUIT:
                game_is_still_running = false;
                break;
            }
        }

        if (update) {
            //std::cout << "UPDATE" << std::endl;

            // get key states and update
            currentKeyStates = SDL_GetKeyboardState( NULL );
            if( currentKeyStates[ SDL_SCANCODE_UP ] )
            {
                player_position_y -= 1;
            }
            else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
            {
                player_position_y += 1;
            }
            else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
            {
                player_position_x -= 1;
            }
            else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
            {
                player_position_x += 1;
            }

            // update game state, draw the current frame
        }

        if (render) {
            //std::cout << "RENDER" << std::endl;

            // Clear screen
            SDL_SetRenderDrawColor(this->sdl_renderer, 0xFF, 0x00, 0xFF, 0xFF);
            SDL_RenderClear(this->sdl_renderer);

            // Render texture to screen
            // SDL_RenderCopy( this->sdl_renderer, gTexture, NULL, NULL );

            //Render red filled quad
            SDL_Rect fillRect = { player_position_x, player_position_y, 20, 20 };
            SDL_SetRenderDrawColor( this->sdl_renderer, 0xFF, 0x00, 0x00, 0xFF );
            SDL_RenderFillRect( this->sdl_renderer, &fillRect );

            // Update screen
            SDL_RenderPresent(this->sdl_renderer);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
