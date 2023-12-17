#ifndef RIGID_BODY_HPP_
#define RIGID_BODY_HPP_

#include "vector2.hpp"

using Position = Vector2<float>;
using Velocity = Vector2<float>;

typedef struct
{
    Position position;
    Velocity linear_velocity;
    float angle;
    float angularVelocity;
    float mass;
} RigidBody;

#endif // RIGID_BODY_HPP_
