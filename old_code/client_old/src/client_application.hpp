#ifndef CLIENT_APPLICATION_HPP_
#define CLIENT_APPLICATION_HPP_

#include <window.hpp>

enum ClientApplicationState
{
    Disconnected,
    Connecting,
    Connected
};

class ClientApplication
{
public:
    ClientApplication(std::shared_ptr<Window> window) {};
    void run();
private:
    void run_disconnect_iteration();
    void run_connecting_iteration();
    void run_connected_iteration();
    bool application_is_running = false;
    ClientApplicationState state = Disconnected;
};

#endif // CLIENT_APPLICATION_HPP_
