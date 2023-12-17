#include <iostream>
#include <logger.hpp>
#include <version.hpp>
#include <event_handler.hpp>
#include <input_handler.hpp>
#include <window.hpp>
#include <client_application.hpp>
#include <renderer.hpp>

int main()
{
    Logger::info("Game Client v{}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

    EventHandler event_handler;
    InputHandler input_handler;
    Window window;
    PhysicsSimulator physics_simulator;
    GameState game_state;
    Renderer renderer(window);
    ClientApplication app(event_handler, input_handler, window, physics_simulator, game_state, renderer);

    try
    {
        app.create_dummy_data();
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}