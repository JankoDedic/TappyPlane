#include "SpikePair.hpp"

#include "RectangleFunctions.hpp"
#include "Renderer.hpp"
#include "Spritesheet.hpp"

namespace TappyPlane {

using namespace SDLW::Video;

static auto& topSpikeSourceBounds()
{
    static auto bounds = Spritesheet::instance().sourceBounds("topSpike");
    return bounds;
}

static auto& bottomSpikeSourceBounds()
{
    static auto bounds = Spritesheet::instance().sourceBounds("bottomSpike");
    return bounds;
}

constexpr Rectangle topSpikeBounds{0, -10, 409, 902};

constexpr Rectangle bottomSpikeBounds{0, canvasBounds.height() - 902, 409, 902};

SpikePair::SpikePair()
    : topSpikeBounds(TappyPlane::topSpikeBounds)
    , bottomSpikeBounds(TappyPlane::bottomSpikeBounds)
{
}

int SpikePair::x() const noexcept
{
    return topSpikeBounds.x();
}

void SpikePair::setX(const int value) noexcept
{
    topSpikeBounds.setX(value);
    bottomSpikeBounds.setX(value);
}

void SpikePair::draw() const
{
    Renderer::instance().copy(Spritesheet::instance().texture(),
        topSpikeSourceBounds(), topSpikeBounds);
    Renderer::instance().copy(Spritesheet::instance().texture(),
        bottomSpikeSourceBounds(), bottomSpikeBounds);
}

} // namespace TappyPlane
