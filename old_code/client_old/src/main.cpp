#include <iostream>

#include <logger.hpp>

#include <window.hpp>
#include <client_application.hpp>

int main()
{
    Logger::info("Game Client v0.1");

    Window window;
    ClientApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}