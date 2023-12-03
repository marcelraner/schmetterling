#include "application.hpp"

#include <iostream>

void Application::init()
{
    std::cout << "TRACE: Application::init()" << std::endl;

    //--------------------------------------------------------------------------
    // Initialize SDL subsystems
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "ERROR: SDL_Init(): " << SDL_GetError() << std::endl;
        this->cleanup();
        exit(1);
    }
    this->sdl_has_been_initialized = true;

    //--------------------------------------------------------------------------
    // Create window
    this->sdl_window = SDL_CreateWindow("Sample",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        800, 600,
                                        SDL_WINDOW_RESIZABLE);
    if (this->sdl_window == nullptr)
    {
        std::cerr << "ERROR: SDL_CreateWindow(): " << SDL_GetError() << std::endl;
        this->cleanup();
        exit(1);
    }

    //--------------------------------------------------------------------------
    // Create renderer
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window,
                                            -1,
                                            SDL_RENDERER_ACCELERATED);
    if (this->sdl_renderer == nullptr)
    {
        std::cerr << "ERROR: SDL_CreateRenderer(): " << SDL_GetError() << std::endl;
        this->cleanup();
        exit(1);
    }
    SDL_SetRenderDrawColor(this->sdl_renderer, 0xFF, 0x00, 0xFF, 0xFF);

    //--------------------------------------------------------------------------
}

void Application::cleanup()
{
    std::cout << "TRACE: Application::cleanup()" << std::endl;

    //--------------------------------------------------------------------------
    if (this->sdl_renderer != nullptr)
    {
        SDL_DestroyRenderer(this->sdl_renderer);
        this->sdl_renderer = nullptr;
    }

    //--------------------------------------------------------------------------
    if (this->sdl_window != nullptr)
    {
        SDL_DestroyWindow(this->sdl_window);
        this->sdl_window = nullptr;
    }

    //--------------------------------------------------------------------------
    if (this->sdl_has_been_initialized)
    {
        SDL_Quit();
    }
}

void Application::mainLoop()
{
    std::cout << "TRACE: Application::mainLoop()" << std::endl;

    bool game_is_still_running = true;

    while (game_is_still_running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        { // poll until all events are handled!
            // decide what to do with this event.
            switch (event.type)
            {
            case SDL_QUIT:
                game_is_still_running = false;
                break;
            }
        }

        // update game state, draw the current frame

        // Clear screen
        SDL_RenderClear(this->sdl_renderer);

        // Render texture to screen
        // SDL_RenderCopy( this->sdl_renderer, gTexture, NULL, NULL );

        // Update screen
        SDL_RenderPresent(this->sdl_renderer);
    }
}

void Application::run()
{
    std::cout << "TRACE: Application::run()" << std::endl;

    this->init();
    this->mainLoop();
    this->cleanup();
}
