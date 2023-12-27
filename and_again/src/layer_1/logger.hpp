#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <format>
#include <iostream>
#include <chrono>

namespace Logger
{
    template< class... Args >
    void info( std::format_string<Args...> fmt, Args&&... args )
    {
        std::cout << std::chrono::system_clock::now() << " INFO: " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }

    template< class... Args >
    void debug( std::format_string<Args...> fmt, Args&&... args )
    {
        std::cout << std::chrono::system_clock::now() << " DEBUG: " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }

    template< class... Args >
    void trace( std::format_string<Args...> fmt, Args&&... args )
    {
        std::cout << std::chrono::system_clock::now() << " TRACE: " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }

    template< class... Args >
    void error( std::format_string<Args...> fmt, Args&&... args )
    {
        std::cerr << std::chrono::system_clock::now() << " ERROR: " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }

    template< class... Args >
    void exception( std::format_string<Args...> fmt, Args&&... args )
    {
        std::cout << std::chrono::system_clock::now() << " EXCEPTION: " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    }
};

#endif // LOGGER_HPP_
