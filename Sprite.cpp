#include "Sprite.hpp"

#include "Renderer.hpp"
#include "Spritesheet.hpp"

namespace TappyPlane {

Sprite::Sprite(const std::string& spritesheetKey,
    const SDLW::Video::Rectangle& bounds)
    : mSourceBounds(Spritesheet::instance().sourceBounds(spritesheetKey))
    , mBounds(bounds)
{
}

void Sprite::draw() const
{
    Renderer::instance().copy(Spritesheet::instance().texture(), mSourceBounds,
        mBounds);
}

} // namespace TappyPlane
