#include "SpikePairFactory.hpp"

namespace TappyPlane {

SpikePairFactory::SpikePairFactory(const int spikeTipDistance)
    : mSpikeTipDistance(spikeTipDistance)
    , mRNG(std::make_unique<std::mt19937>(std::random_device{}()))
{
}

SpikePair SpikePairFactory::make() const
{
    const auto offset = mSpikeTipDistance;
    const auto [topSpikeOffset, bottomSpikeOffset] = [&]() {
        const std::uniform_int_distribution<> dist{5, 95};
        const auto breakPoint = float(dist(*mRNG)) / 100;
        return std::make_pair(int(breakPoint * offset),
            int((1.0f - breakPoint) * offset));
    }();
    SpikePair spikePair;
    spikePair.topSpikeBounds.setY(spikePair.topSpikeBounds.y()
        - topSpikeOffset);
    spikePair.bottomSpikeBounds.setY(spikePair.bottomSpikeBounds.y()
        + bottomSpikeOffset);
    return spikePair;
}

} // namespace TappyPlane