#pragma once

#include <memory>
#include <random>

#include "SpikePair.hpp"

namespace TappyPlane {

class SpikePairFactory {
public:
    SpikePairFactory(int spikeTipDistance);

    SpikePair make() const;

private:
    int mSpikeTipDistance;
    std::unique_ptr<std::mt19937> mRNG;
};

} // namespace TappyPlane
