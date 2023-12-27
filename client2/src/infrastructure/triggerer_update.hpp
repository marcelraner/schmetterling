#ifndef TRIGGERER_UPDATE_HPP_
#define TRIGGERER_UPDATE_HPP_

#include <sdl_initializer.hpp>
#include <interface_triggerer.hpp>
#include <triggerer_periodic.hpp>
#include <thread>

class UpdateTriggerer : public PeriodicTriggerer
{
public:
    UpdateTriggerer() : PeriodicTriggerer(std::chrono::milliseconds(8)) {}
};

#endif // TRIGGERER_UPDATE_HPP_
