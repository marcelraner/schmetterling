#include <physics_simulator.hpp>

void PhysicsSimulator::update_rigid_bodies(std::map<uint32_t, RigidBody>& rigid_bodies, std::chrono::nanoseconds dt)
{
    for (auto& rigid_body : rigid_bodies)
    {
        //rigid_body.second.position.x++;
        //rigid_body.second.position.y++;
    }
}
