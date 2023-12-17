#ifndef INPUTHANDLER_HPP_
#define INPUTHANDLER_HPP_

#include <sdl_initializer.hpp>

#include <functional>

class InputHandler
{
public:
    InputHandler() {}
    void handleInput();
private:
    SdlInitializer sdl_initializer;
};

#endif // INPUTHANDLER_HPP_
