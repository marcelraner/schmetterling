#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <tuple>
#include <vector>

/*class IRenderable {
public:
    virtual void render(IRenderer& renderer) = 0;
};

class IRenderer {
public:
    virtual void clear_surface();
    virtual void render_renderables(std::vector<IRenderable> renderables) = 0;
    virtual void present_rendered_on_surface();
    virtual void draw_rectangle(int32_t x, int32_t y, int32_t h, int32_t w) = 0;
    virtual void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = 0;
};

class IWindow {
public:
    virtual void clear() = 0;
    virtual void present() = 0;
    virtual std::tuple<int32_t, int32_t> size() = 0;
    virtual void draw_rectangle(int32_t x, int32_t y, int32_t h, int32_t w) = 0;
    virtual void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2) = 0;
};



class MockWindow : public IWindow {
public:
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(void, present, (), (override));
    MOCK_METHOD((std::tuple<int32_t, int32_t>), size, (), (override));
    MOCK_METHOD(void, draw_rectangle, (int32_t x, int32_t y, int32_t h, int32_t w), (override));
    MOCK_METHOD(void, draw_line, (int32_t x1, int32_t y1, int32_t x2, int32_t y2), (override));
};

class SomeRenderableObject : public IRenderable {
    void render(IRenderer& renderer) {
        renderer.draw_line(0, 0, 100, 100);
    }
};

class SomeRenderer : IRenderer {
public:
    SomeRenderer(IWindow& window) : window{window} {};
    void clear_surface()
    {
        window.clear();
    }

    void render_renderables(std::vector<IRenderable> renderables)
    {
        this->window.clear();
        this->window.draw_line(0, 0, 100, 100);
        this->window.present();
    }

    void present_rendered_on_surface()
    {
        window.present();
    }

private:
    IWindow& window;
};*/

TEST(RenderHandlerSuite, RenderHandlerTest)
{
    /*MockWindow mock_window;
    SomeRenderer renderer(mock_window);
    std::vector<IRenderable> renderables;

    EXPECT_CALL(mock_window, size())
        .WillRepeatedly(testing::Return(std::tuple<int32_t, int32_t>(800, 600)));

    renderables.push_back(SomeRenderableObject());

    renderer.clear_surface();
    renderer.render_renderables(renderables);
    renderer.present_rendered_on_surface();

    auto result = mock_window.size();*/

    //EXPECT_EQ(result, (std::tuple<int32_t, int32_t>(11, 20)));
    /*MockWindow mock_window;

    IRenderer& renderer = Renderer();

    renderer.render();

    
    EXPECT_EQ(renderer.size(), 3);*/
}
