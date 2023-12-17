#ifndef SERVER_APPLICATION_HPP_
#define SERVER_APPLICATION_HPP_

#include <map>
#include <cstdint>
#include <rigid_body.hpp>


/*struct Asteroid
{
    Position position;
};

struct Spaceship
{

};

struct Universe
{
    std::array<Asteroid, 1000> asteroids;
    std::array<Spaceship, 100> spaceships;
};

struct Player
{

};*/

class GameState
{
public:
    std::map<uint32_t, RigidBody> rigid_bodies;
private:
    //std::vector<Player> players;
    //std::map<std::string, int> players;
};

enum ServerApplicationState
{
    Starting,
    Started
};

class ServerApplication
{
public:
    ServerApplication() {};
    void run();
private:
    bool application_is_running = false;
    ServerApplicationState state = Starting;
    GameState game_state;
};

#endif // SERVER_APPLICATION_HPP_
