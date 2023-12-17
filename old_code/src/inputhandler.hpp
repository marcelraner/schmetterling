#ifndef INPUTHANDLER_HPP_
#define INPUTHANDLER_HPP_

#include "subsysteminitializer.hpp"

#include <functional>

class InputHandler
{
public:
    InputHandler() {}
    void handleInput();
private:
    SdlSubsystemInitializer sdl_subsystem_initializer;
};

#endif // INPUTHANDLER_HPP_
