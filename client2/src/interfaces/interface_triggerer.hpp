#ifndef INTERFACE_TRIGGERER_HPP_
#define INTERFACE_TRIGGERER_HPP_

#include <cstdint>

class ITriggerer
{
public:
    virtual void activate(uint32_t custom_triggerer_event_type, int32_t custom_triggerer_code) = 0;
    virtual void deactivate() = 0;
};

#endif // INTERFACE_TRIGGERER_HPP_
