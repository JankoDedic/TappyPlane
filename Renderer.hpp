#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

constexpr SDLW::Video::Rectangle canvasBounds{0, 0, 1080, 1920};

class Renderer : public SDLW::Video::Renderer {
public:
    static Renderer& instance();

private:
    Renderer();
};

} // namespace TappyPlane
