#include "Renderer.hpp"

#include "Window.hpp"

namespace TappyPlane {

Renderer& Renderer::instance()
{
    static Renderer renderer;
    return renderer;
}

Renderer::Renderer()
    : SDLW::Video::Renderer(Window::instance(),
        SDLW::Video::Renderer::Flags::Accelerated)
{
    setLogicalSize(canvasBounds.size());
    setDrawBlendMode(SDLW::Video::BlendMode::Blend);
}

} // namespace TappyPlane
