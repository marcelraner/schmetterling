#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <position.hpp>

class Camera
{
public:
    Camera() {
        camera_position.x = 0;
        camera_position.y = 0;
    };
    Position camera_position; // maybe replace with reference
};

#endif // GAME_STATE_HPP_
