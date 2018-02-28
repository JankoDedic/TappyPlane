#include "Plane.hpp"

#include "Renderer.hpp"
#include "Spritesheet.hpp"

namespace TappyPlane {

using namespace SDLW::Video;

static auto& sourceBounds()
{
    static auto bounds = Spritesheet::instance().sourceBounds("plane");
    return bounds;
}

constexpr Rectangle baseBounds{250, canvasBounds.height()/2 - 192/2, 231, 192};

constexpr int initialVerticalVelocity{5};

Plane::Plane()
    : mBaseBounds(baseBounds)
    , mBounds(mBaseBounds)
    , mVerticalVelocity{initialVerticalVelocity}
{
}

SDLW::Video::Rectangle Plane::bounds() const noexcept
{
    return mBounds;
}

bool Plane::isPlaying() const noexcept
{
    return mIsPlaying;
}

void Plane::play() noexcept
{
    mIsPlaying = true;
}

void Plane::pause() noexcept
{
    mIsPlaying = false;
}

void Plane::reset() noexcept
{
    mBounds = mBaseBounds;
    mVerticalVelocity = initialVerticalVelocity;
}

void Plane::jump() noexcept
{
    mVerticalVelocity += mJumpVelocityBoost;
}

void Plane::update() noexcept
{
    if (!isPlaying()) {
        return;
    }
    if (mVerticalVelocity < mVerticalTerminalVelocity) {
        mVerticalVelocity += mGravityVelocity;
    }
    mBounds.setY(mBounds.y() + mVerticalVelocity);
}

void Plane::draw() const
{
    Renderer::instance().copy(Spritesheet::instance().texture(),
        sourceBounds(), mBounds);
}

} // namespace TappyPlane
