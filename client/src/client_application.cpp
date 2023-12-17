#include <client_application.hpp>

#include <logger.hpp>
#include <chrono>
#include <thread>

// TODO: config values. need to be implemented into some kind of configuration manager
#define CONFIG_GET_INPUT_INTERVAL_US 4000
#define CONFIG_UPDATE_INTERVAL_US 16667
#define CONFIG_SYNC_INTERVAL_US 16667
#define CONFIG_RENDER_INTERVAL_US 16667

void ClientApplication::run()
{
    Logger::trace("ClientApplication::run()");

    auto time_now = std::chrono::system_clock::now();
    auto last_time_get_input = time_now;
    auto last_time_update = time_now;
    auto last_time_sync = time_now;
    auto last_time_render = time_now;

    this->application_is_running = true;

    while (this->application_is_running) {
        auto time_now = std::chrono::system_clock::now();

        if ((last_time_get_input + std::chrono::microseconds(CONFIG_GET_INPUT_INTERVAL_US)) < time_now)
        {
            this->get_input();
            last_time_get_input = time_now;
        }

        while ((last_time_update + std::chrono::microseconds(CONFIG_UPDATE_INTERVAL_US)) < time_now)
        {
            this->update_state(std::chrono::microseconds(CONFIG_UPDATE_INTERVAL_US));
            last_time_update += std::chrono::microseconds(CONFIG_UPDATE_INTERVAL_US);
        }

        if ((last_time_sync + std::chrono::microseconds(CONFIG_SYNC_INTERVAL_US)) < time_now)
        {
            this->sync_with_server();
            last_time_sync = time_now;
        }

        if ((last_time_render + std::chrono::microseconds(CONFIG_RENDER_INTERVAL_US)) < time_now)
        {
            this->render();
            last_time_render = time_now;
        }

        auto next_input = last_time_get_input + std::chrono::microseconds(CONFIG_GET_INPUT_INTERVAL_US);
        auto next_update = last_time_update + std::chrono::microseconds(CONFIG_UPDATE_INTERVAL_US);
        auto next_sync = last_time_sync + std::chrono::microseconds(CONFIG_SYNC_INTERVAL_US);
        auto next_render = last_time_render + std::chrono::microseconds(CONFIG_RENDER_INTERVAL_US);

        auto sleep_until_time = next_input;
        if (next_update < sleep_until_time) sleep_until_time = next_update;
        if (next_sync < sleep_until_time) sleep_until_time = next_sync;
        if (next_render < sleep_until_time) sleep_until_time = next_render;

        std::this_thread::sleep_until(sleep_until_time);
    }
}

void ClientApplication::quit()
{
    Logger::trace("ClientApplication::quit()");
    this->application_is_running = false;
}

void ClientApplication::get_input()
{
    //Logger::trace("ClientApplication::get_input()");
    this->input_handler.handleInput();
}

void ClientApplication::update_state(std::chrono::nanoseconds dt)
{
    //Logger::trace("ClientApplication::update_state()");
    this->event_handler.handleEvents();
    this->physics_simulator.update_rigid_bodies(this->game_state.rigid_bodies, dt);
}

void ClientApplication::sync_with_server()
{
    //Logger::trace("ClientApplication::sync_with_server()");
    // ? this->event_handler.handleNetworkEvents();
    // this->network_manager.receive();
}

void ClientApplication::render()
{
    //Logger::trace("ClientApplication::render()");
    this->renderer.clear();
    this->renderer.render_rigid_bodies(this->game_state.rigid_bodies);
    this->renderer.present();
}

void ClientApplication::create_dummy_data()
{
    // asteroid 1
    auto rigid_body = RigidBody {
        Position {
            100,
            100
        },
        Velocity {
            0,
            0
        },
        0.0f,
        0.0f,
        0.0f
    };
    this->game_state.rigid_bodies.insert({0, rigid_body});

    // asteroid 2
    rigid_body.position.x = 300;
    rigid_body.position.y = 300;
    this->game_state.rigid_bodies.insert({1, rigid_body});

    // spaceship 1 (player)
    rigid_body.position.x = 200;
    rigid_body.position.y = 200;
    this->game_state.rigid_bodies.insert({2, rigid_body});
}
