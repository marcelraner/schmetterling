#include <renderer.hpp>

void Renderer::clear()
{
    window.clear();
}
void Renderer::present()
{
    window.present();
}

void Renderer::render_rigid_bodies(std::map<uint32_t, RigidBody> &rigid_bodies)
{
    window.draw_rectangle(0, 0, 0, 0);
    for (auto& rigid_body : rigid_bodies)
    {
        window.draw_rectangle(
            rigid_body.second.position.x - 10,
            rigid_body.second.position.y - 10,
            20,
            20);
    }
}
