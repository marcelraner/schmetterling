#include "client_application.hpp"

#include <logger.hpp>
#include <time_frame.hpp>
#include "network_handler.hpp"
#include "entity_manager.hpp"

void ClientApplication::run()
{
    Logger::trace("ClientApplication::run()");

    NetworkHandler network_handler;
    EntityManager entity_manager;
    //GameClient game_client;

    TimeFrame time_frame;

    // set frame duration to 4ms because of input polling
    // the update and rendering will be limited to the framerate (default 60hz (~16ms))
    time_frame.set_frame_duration(4);

    this->application_is_running = true;
    while (this->application_is_running) {
        time_frame.start_frame();

        switch (this->state) {
        case Disconnected:
            this->run_disconnect_iteration();
            break;
        case Connecting:
            this->run_connecting_iteration();
            
            break;
        case Connected:
            this->run_connected_iteration();
            
            break;
        }

        time_frame.sleep_until_frame_is_over();
    }
}

void ClientApplication::run_disconnect_iteration()
{
    // show connect dialog or wait for extern trigger
    /*if (network_handler.connect()) {
        Logger::debug("Switching state to Connecting");
        this->state = Connecting;
    }*/
}

void ClientApplication::run_connecting_iteration()
{
    // try to connect and switch state to connected or disconnected
    /*Logger::debug("Switching state to Connecting");
    this->state = Connected;*/
}

void ClientApplication::run_connected_iteration()
{
    // update gamestate
    /*network_handler.send();
    network_handler.recv();*/
}
