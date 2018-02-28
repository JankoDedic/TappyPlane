#include "InfiniteSideScrollingSprite.hpp"

#include "RectangleFunctions.hpp"
#include "Renderer.hpp"
#include "Spritesheet.hpp"

namespace TappyPlane {

using namespace SDLW::Video;

InfiniteSideScrollingSprite::InfiniteSideScrollingSprite(
    const std::string& spritesheetKey, const SDLW::Video::Rectangle& bounds,
    const float pixelsPerFrame)
    : mSourceBounds(Spritesheet::instance().sourceBounds(spritesheetKey))
    , mBounds(bounds)
    , mSourceSlice((float)leftOf(mSourceBounds), (float)rightOf(mSourceBounds),
        (float)sourceSliceWidth())
    , mScrollSpeed(toSourceSpeed(pixelsPerFrame))
    , mSourceBounds1(horizontalSlice((int)mSourceSlice.leftEnd(),
        (int)mSourceSlice.rightEnd(), mSourceBounds))
    , mDestinationBounds1(mBounds)
{
}

const Rectangle& InfiniteSideScrollingSprite::bounds() const noexcept
{
    return mBounds;
}

bool InfiniteSideScrollingSprite::isPlaying() const noexcept
{
    return mIsPlaying;
}

void InfiniteSideScrollingSprite::play() noexcept
{
    mIsPlaying = true;
}

void InfiniteSideScrollingSprite::pause() noexcept
{
    mIsPlaying = false;
}

void InfiniteSideScrollingSprite::update() noexcept
{
    if (!mIsPlaying) {
        return;
    }
    mSourceSlice += mScrollSpeed;
    if (!mSourceSlice.isWrapped()) {
        mSourceBounds1 = horizontalSlice((int)mSourceSlice.leftEnd(),
            (int)mSourceSlice.rightEnd(), mSourceBounds);
        mSourceBounds2.setWidth(0);
        mDestinationBounds1 = mBounds;
        mDestinationBounds2.setWidth(0);
    } else {
        mSourceBounds1 = horizontalSlice((int)mSourceSlice.leftEnd(),
            (int)mSourceSlice.rightBound(), mSourceBounds);
        mSourceBounds2 = horizontalSlice((int)mSourceSlice.leftBound(),
            (int)mSourceSlice.rightEnd(), mSourceBounds);
        const auto destinationSplitPoint = 1.0f
            - mSourceSlice.leftPieceLength() / mSourceSlice.length();
        std::tie(mDestinationBounds1, mDestinationBounds2) =
            horizontalSplit(destinationSplitPoint, mBounds);
    }
}

void InfiniteSideScrollingSprite::draw() const
{
    Renderer::instance().copy(Spritesheet::instance().texture(),
        mSourceBounds1, mDestinationBounds1);
    Renderer::instance().copy(Spritesheet::instance().texture(),
        mSourceBounds2, mDestinationBounds2);
}

int InfiniteSideScrollingSprite::sourceSliceWidth() const
{
    auto size = mBounds.size();
    scaleToFit(size, mSourceBounds.size());
    return size.width();
}

float InfiniteSideScrollingSprite::toSourceSpeed(const float destinationSpeed)
    const noexcept
{
    return (destinationSpeed * mSourceBounds.width()) / mBounds.width();
}

} // namespace TappyPlane
