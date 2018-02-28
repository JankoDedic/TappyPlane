#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

class Plane {
public:
    Plane();

    SDLW::Video::Rectangle bounds() const noexcept;

    bool isPlaying() const noexcept;

    void play() noexcept;

    void pause() noexcept;

    void reset() noexcept;

    void jump() noexcept;

    void update() noexcept;

    void draw() const;

private:
    bool mIsPlaying = false;
    SDLW::Video::Rectangle mBaseBounds;
    SDLW::Video::Rectangle mBounds;
    int mVerticalVelocity;
    int mVerticalTerminalVelocity{18};
    int mGravityVelocity{1};
    int mJumpVelocityBoost{-35};
};

} // namespace TappyPlane
