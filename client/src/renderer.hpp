#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <window.hpp>
#include <map>
#include <rigid_body.hpp>
#include <cstdint>
#include <camera.hpp>

class Renderer
{
public:
    Renderer(Window& window, Camera& camera) : window{window}, camera{camera} {};
    void clear();
    void present();
    void render_camera();
    void render_grid();
    void render_rigid_bodies(std::map<uint32_t, RigidBody>& rigid_bodies);
private:
    Window& window;
    Camera& camera;
};

#endif // RENDERER_HPP_
