#ifndef TRIGGERER_RENDER_HPP_
#define TRIGGERER_RENDER_HPP_

#include <sdl_initializer.hpp>
#include <interface_triggerer.hpp>
#include <triggerer_periodic.hpp>
#include <thread>

class RenderTriggerer : public PeriodicTriggerer
{
public:
    RenderTriggerer() : PeriodicTriggerer(std::chrono::milliseconds(16)) {}
};

#endif // TRIGGERER_RENDER_HPP_
