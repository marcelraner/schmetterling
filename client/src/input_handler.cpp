#include <input_handler.hpp>

#include <iostream>

void InputHandler::handleInput()
{
    // handle hold keys
    auto currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_W ] )
    {
        // start accelerating up
    }
    else
    {
        // stop accelerating up
    }

    if( currentKeyStates[ SDL_SCANCODE_A ] )
    {
        // start accelerating left
    }
    else
    {
        // stop accelerating left
    }

    if( currentKeyStates[ SDL_SCANCODE_S ] )
    {
        // start accelerating down
    }
    else
    {
        // stop accelerating down
    }

    if( currentKeyStates[ SDL_SCANCODE_D ] )
    {
        // start accelerating right
    }
    else
    {
        // stop accelerating right
    }
}
