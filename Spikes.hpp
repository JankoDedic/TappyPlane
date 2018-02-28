#pragma once

#include <vector>

#include "SpikePairFactory.hpp"

namespace TappyPlane {

class Spikes {
public:
    Spikes(int spikePairDistance, int scrollSpeed);

    std::pair<std::vector<SpikePair>::const_iterator,
        std::vector<SpikePair>::const_iterator> bounds() const noexcept;

    bool isPlaying() const noexcept;

    void play() noexcept;

    void pause() noexcept;

    void reset() noexcept;

    void update() noexcept;

    void draw() const;

private:
    bool mIsPlaying = false;
    SpikePairFactory mSpikePairFactory;
    int mSpikePairDistance;
    int mScrollSpeed;
    std::vector<SpikePair> mSpikePairs;
};

} // namespace TappyPlane
