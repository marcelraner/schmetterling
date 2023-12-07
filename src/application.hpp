#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

class Application
{
public:
    Application() {};
    void run();
    void quit();
private:
    bool application_is_running = false;
};

#endif // APPLICATION_HPP_
