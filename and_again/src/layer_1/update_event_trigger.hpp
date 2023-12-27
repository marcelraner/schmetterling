#ifndef TRIGGERER_UPDATE_HPP_
#define TRIGGERER_UPDATE_HPP_

#include <event_trigger.hpp>

class UpdateEventTrigger
{
public:
    UpdateEventTrigger() : EventTrigger(std::chrono::milliseconds(8)) {}
};

#endif // TRIGGERER_UPDATE_HPP_