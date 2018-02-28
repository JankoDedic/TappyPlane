#pragma once

#include <string>

#include "SDLW.hpp"

namespace TappyPlane {

class Sprite {
public:
    Sprite(const std::string& spritesheetKey,
        const SDLW::Video::Rectangle& bounds);

    void draw() const;

private:
    SDLW::Video::Rectangle mSourceBounds;
    SDLW::Video::Rectangle mBounds;
};

} // namespace TappyPlane
