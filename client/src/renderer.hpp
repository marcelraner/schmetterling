#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <window.hpp>
#include <map>
#include <rigid_body.hpp>
#include <cstdint>

class Renderer
{
public:
    Renderer(Window& window) : window{window} {};
    void clear();
    void present();
    void render_rigid_bodies(std::map<uint32_t, RigidBody>& rigid_bodies);
private:
    Window& window;
};

#endif // RENDERER_HPP_
