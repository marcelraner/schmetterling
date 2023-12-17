#include "inputhandler.hpp"

#include <iostream>

void InputHandler::handleInput()
{
    auto currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        std::cout << "DEBUG: Key UP is pressed" << std::endl;
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        std::cout << "DEBUG: Key DOWN is pressed" << std::endl;
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        std::cout << "DEBUG: Key LEFT is pressed" << std::endl;
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        std::cout << "DEBUG: Key RIGHT is pressed" << std::endl;
    }
}
