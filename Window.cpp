#include "Window.hpp"

#include "RectangleFunctions.hpp"

namespace TappyPlane {

constexpr auto title = "Tappy Plane";
constexpr SDLW::Video::Size aspectRatio{9, 16};
constexpr double debugScale{0.9};

static SDLW::Video::Size size()
{
    auto resultSize = aspectRatio;
    scaleToFit(resultSize, SDLW::Video::Display::usableBounds(0).size());
    scale(resultSize, debugScale);
    return resultSize;
}

Window& Window::instance()
{
    static Window window;
    return window;
}

Window::Window()
    : SDLW::Video::Window(::TappyPlane::title,
        {SDLW::Video::Window::positionCentered, ::TappyPlane::size()},
        SDLW::Video::Window::Flags::Shown)
{
}

} // namespace TappyPlane
