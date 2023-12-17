#include <iostream>

#include "server_application.hpp"
#include <logger.hpp>

int main()
{
    std::cout << "Running Server ..." << std::endl;
    Logger::trace("main()");

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