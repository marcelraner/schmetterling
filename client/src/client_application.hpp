#ifndef CLIENT_APPLICATION_HPP_
#define CLIENT_APPLICATION_HPP_

#include <event_handler.hpp>
#include <input_handler.hpp>
#include <window.hpp>
#include <physics_simulator.hpp>
#include <game_state.hpp>
#include <renderer.hpp>
#include <camera.hpp>

class ClientApplication
{
public:
    ClientApplication(EventHandler& event_handler,
                      InputHandler& input_handler,
                      Window& window,
                      PhysicsSimulator& physics_simulator,
                      GameState& game_state,
                      Renderer& renderer,
                      Camera& camera)
                      :
                      event_handler{event_handler},
                      input_handler{input_handler},
                      window{window},
                      physics_simulator{physics_simulator},
                      game_state{game_state},
                      renderer{renderer},
                      camera{camera}
    {
        this->event_handler.registerOnQuitCallback(std::bind(&ClientApplication::quit, this));
    };
    void run();
    void quit();
    void create_dummy_data(); // TODO: for filling game with life before the life is implemented (need to be removed later)
private:
    void get_input();
    void update_state(std::chrono::nanoseconds dt);
    void sync_with_server();
    void render();
private:
    bool application_is_running = false;
    EventHandler& event_handler;
    InputHandler& input_handler;
    PhysicsSimulator& physics_simulator;
    GameState& game_state;
    Window& window;
    Renderer& renderer;
    Camera& camera;
};

#endif // CLIENT_APPLICATION_HPP_
