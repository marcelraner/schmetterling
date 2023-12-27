#include <renderer.hpp>

void Renderer::render()
{
    this->clear();
    this->render_camera();
    this->present();
}

void Renderer::clear()
{
    window.clear();
}

void Renderer::present()
{
    window.present();
}

void Renderer::render_camera()
{
    auto window_size = window.get_size();
    auto camera_position = camera.camera_position;

    // draw horizontal line
    window.draw_line(10, camera_position.y, window_size.width - 10, camera_position.y);

    // draw vertical line
    window.draw_line(camera_position.x, 10, camera_position.x, window_size.height - 10);
}

void Renderer::render_grid()
{
    auto window_size = window.get_size();
    auto camera_position = camera.camera_position;

    // draw horizontal lines
    for (int y = 0; y < window_size.height; y+=100)
    {
        window.draw_line(10, y, window_size.width - 10, y);
    }

    // draw vertical lines
    for (int x = 0; x < window_size.width; x+=100)
    {
        window.draw_line(x, 10, x, window_size.height - 10);
    }
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
