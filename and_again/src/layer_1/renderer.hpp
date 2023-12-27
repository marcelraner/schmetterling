#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <window.hpp>

class Renderer
{
public:
    Renderer(Window &window);
    void clear();
    void present();
    /*void render_camera();
    void render_grid();
    void render_rigid_bodies(std::map<uint32_t, RigidBody> &rigid_bodies);*/

private:
    Window &window;
    SDL_Renderer *sdl_renderer = nullptr;
};

#endif // RENDERER_HPP_
