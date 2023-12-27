#include <application.hpp>

#include <interface_triggerer.hpp>
#include <triggerer_update.hpp>
#include <triggerer_render.hpp>
#include <window.hpp>
#include <camera.hpp>
#include <renderer.hpp>
#include <event_handler.hpp>

#include <iostream>

Application::Application() = default;
Application::~Application() = default;

void Application::run()
{
    UpdateTriggerer update_triggerer;
    RenderTriggerer render_triggerer;
    EventHandler event_handler(update_triggerer, render_triggerer);
    Window window;
    Camera camera;
    Renderer renderer(window, camera);

    event_handler.registerOnRenderCallback(std::bind(&Renderer::render, renderer));

    event_handler.loop();
}
