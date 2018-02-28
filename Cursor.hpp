#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

class Cursor {
public:
    Cursor();

    void handleEvent(const SDLW::Events::Event&);

    void draw() const;

private:
    bool mIsPressed = false;
    SDLW::Video::Point mPosition{0, 0};
    SDLW::Video::Rectangle mNormalSourceBounds;
    SDLW::Video::Rectangle mPressedSourceBounds;
    SDLW::Video::Size mNormalSize;
    SDLW::Video::Size mPressedSize;
};

} // namespace TappyPlane
