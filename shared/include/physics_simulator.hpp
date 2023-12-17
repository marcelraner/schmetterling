#ifndef PHYSICS_SIMULATOR_HPP_
#define PHYSICS_SIMULATOR_HPP_

#include <map>
#include <cstdint>
#include <chrono>

#include <rigid_body.hpp>
 
class PhysicsSimulator {
public:
    void update_rigid_bodies(std::map<uint32_t, RigidBody>& rigid_bodies, std::chrono::nanoseconds dt);
};

#endif // PHYSICS_SIMULATOR_HPP_
