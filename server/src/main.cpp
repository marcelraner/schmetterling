#include <iostream>

#include "server_application.hpp"
#include <logger.hpp>

int main()
{
    Logger::info("Game Server v0.1");

    ServerApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        Logger::exception("{}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}