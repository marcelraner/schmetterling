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
    void render(); // TODO: remove or transform into render(renderables)
    void clear();
    void present();
    void render_camera(); // TODO: make renderable
    void render_grid(); // TODO: make renderable
    void render_rigid_bodies(std::map<uint32_t, RigidBody>& rigid_bodies); // TODO: make renderable
private:
    Window& window;
    Camera& camera; // TODO: make renderable
};

#endif // RENDERER_HPP_
