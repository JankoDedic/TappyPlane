#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

class SpikePair {
public:
    SpikePair();

    int x() const noexcept;

    void setX(int) noexcept;

    void draw() const;

    SDLW::Video::Rectangle topSpikeBounds;
    SDLW::Video::Rectangle bottomSpikeBounds;
};

} // namespace TappyPlane
