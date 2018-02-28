#pragma once

#include "SDLW.hpp"

#include "BoundedSlice.hpp"

namespace TappyPlane {

class InfiniteSideScrollingSprite {
public:
    InfiniteSideScrollingSprite(const std::string& spritesheetKey,
        const SDLW::Video::Rectangle& bounds, float pixelsPerFrame);

    const SDLW::Video::Rectangle& bounds() const noexcept;

    bool isPlaying() const noexcept;

    void play() noexcept;

    void pause() noexcept;

    void update() noexcept;

    void draw() const;

private:
    int sourceSliceWidth() const;

    float toSourceSpeed(float destinationSpeed) const noexcept;

    bool mIsPlaying = false;
    SDLW::Video::Rectangle mSourceBounds;
    SDLW::Video::Rectangle mBounds;
    BoundedSlice<float> mSourceSlice;
    float mScrollSpeed;
    SDLW::Video::Rectangle mSourceBounds1;
    SDLW::Video::Rectangle mSourceBounds2;
    SDLW::Video::Rectangle mDestinationBounds1;
    SDLW::Video::Rectangle mDestinationBounds2;
};

} // namespace TappyPlane
