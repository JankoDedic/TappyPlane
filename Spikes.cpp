#include "Spikes.hpp"

#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace TappyPlane {

constexpr int spikeTipDistance{720};

Spikes::Spikes(const int spikePairDistance, const int scrollSpeed)
    : mSpikePairFactory(spikeTipDistance)
    , mSpikePairDistance(spikePairDistance)
    , mScrollSpeed(scrollSpeed)
{
    reset();
}

std::pair<std::vector<SpikePair>::const_iterator,
    std::vector<SpikePair>::const_iterator> Spikes::bounds() const noexcept
{
    return {cbegin(mSpikePairs), cend(mSpikePairs)};
}

bool Spikes::isPlaying() const noexcept
{
    return mIsPlaying;
}

void Spikes::play() noexcept
{
    mIsPlaying = true;
}

void Spikes::pause() noexcept
{
    mIsPlaying = false;
}

void Spikes::reset() noexcept
{
    constexpr int numSpikePairs{5};
    mSpikePairs.reserve(numSpikePairs);
    for (int i{0}; i < numSpikePairs; ++i) {
        mSpikePairs.push_back(mSpikePairFactory.make());
    }
    const auto stride = mSpikePairs.front().topSpikeBounds.width()
        + mSpikePairDistance;
    auto currentX = rightOf(canvasBounds);
    for (auto& spikePair : mSpikePairs) {
        spikePair.setX(currentX);
        currentX += stride;
    }
}

void Spikes::update() noexcept
{
    if (!isPlaying()) {
        return;
    }
    for (auto& spikePair : mSpikePairs) {
        spikePair.setX(spikePair.x() - mScrollSpeed);
    }
    if (rightOf(mSpikePairs.front().topSpikeBounds) < leftOf(canvasBounds)) {
        mSpikePairs.erase(cbegin(mSpikePairs));
        mSpikePairs.emplace_back(mSpikePairFactory.make()).setX(
            mSpikePairs.back().x() + mSpikePairs.back().topSpikeBounds.width()
            + mSpikePairDistance);
    }
}

void Spikes::draw() const
{
    for (const auto& spikePair : mSpikePairs) {
        spikePair.draw();
    }
}

} // namespace TappyPlane
