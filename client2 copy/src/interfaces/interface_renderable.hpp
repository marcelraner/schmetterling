#ifndef INTERFACE_RENDERABLE_HPP_
#define INTERFACE_RENDERABLE_HPP_

#include <interface_renderer.hpp>

class IRenderable
{
public:
    virtual void render(IRenderer renderer) = 0;
};

#endif // INTERFACE_RENDERABLE_HPP_
