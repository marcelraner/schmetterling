#ifndef RIGID_BODY_HPP_
#define RIGID_BODY_HPP_

#include <position.hpp>
#include <velocity.hpp>

typedef struct
{
    Position position;
    Velocity linear_velocity;
    float angle;
    float angularVelocity;
    float mass;
} RigidBody;

#endif // RIGID_BODY_HPP_
