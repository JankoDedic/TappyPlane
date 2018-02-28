#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

class Window : public SDLW::Video::Window {
public:
    static Window& instance();

private:
    Window();
};

} // namespace TappyPlane
