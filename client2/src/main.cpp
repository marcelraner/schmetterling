#include <logger.hpp>

#include <application.hpp>

int main()
{
    Application app;

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
