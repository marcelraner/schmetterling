#ifndef GAME_STATE_HPP_
#define GAME_STATE_HPP_

#include <map>
#include <cstdint>

#include <rigid_body.hpp>

class GameState
{
public:
    GameState() {};
    std::map<uint32_t, RigidBody> rigid_bodies;
};

#endif // GAME_STATE_HPP_
