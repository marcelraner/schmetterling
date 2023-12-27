#include <iostream>
#include <logger.hpp>
#include <version.hpp>
#include <client_application.hpp>

int main()
{
    Logger::info("Game Client v{}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

    ClientApplication app;
    
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
