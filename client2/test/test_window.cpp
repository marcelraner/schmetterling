#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Window
{
public:
    Window();
    ~Window();
    void clear();
    void present();
    Size2<int32_t> get_size();
    void draw_rectangle(int32_t x, int32_t y, int32_t h, int32_t w);
    void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
private:
    SdlInitializer sdl_initializer;
    SDL_Window *sdl_window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
};