#include "server_application.hpp"

#include <logger.hpp>
#include <time_frame.hpp>
#include "network_handler.hpp"
#include <physics_simulator.hpp>

void ServerApplication::run()
{
    Logger::trace("ServerApplication::run()");

    NetworkHandler network_handler;

    TimeFrame time_frame;
    time_frame.set_frame_duration(1000);

    this->application_is_running = true;
    while (this->application_is_running) {
        time_frame.start_frame();

        auto rigid_body = RigidBody {
                Position {
                    10,
                    20
                },
                Velocity {
                    10,
                    20
                },
                0.0f,
                0.0f,
                0.0f
            };

        switch (this->state) {
        case Starting:
            // load rigid bodies
            this->game_state.rigid_bodies.insert({0, rigid_body});
            rigid_body.position.x = 200;
            rigid_body.position.y = 112;
            this->game_state.rigid_bodies.insert({1, rigid_body});
            // switch to started if all things are initialized
            if (network_handler.open()) {
                Logger::debug("Switching state to Started");
                this->state = Started;
            }
            break;
        case Started:
            // accept connections and handle incoming packets
            network_handler.echo();
            // update game state
            PhysicsSimulator::update_rigid_bodies(this->game_state.rigid_bodies);
            // debug output positions of rigid bodies
            for (const auto& [key, rigid_body] : this->game_state.rigid_bodies)
            {
                Logger::debug("rigid_body: {}: {}, {}",
                    key,
                    rigid_body.position.x,
                    rigid_body.position.y
                );
            }
            // send updates to clients
            break;
        }

        time_frame.sleep_until_frame_is_over();
    }
}
