#include <iostream>

#include "application.hpp"

int main()
{
    std::cout << "TRACE: main()" << std::endl;

    Application app;

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
