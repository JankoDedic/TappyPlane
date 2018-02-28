#include "Spritesheet.hpp"

#include <algorithm>
#include <exception>

#include "Renderer.hpp"

namespace TappyPlane {

using namespace SDLW::Video;

static Texture spritesheetTexture()
{
    constexpr auto spritesheetPath = "Assets/spritesheet.png";
    return SDLW::IMG::loadAsTexture(Renderer::instance(), spritesheetPath);
}

static std::vector<std::pair<std::string, Rectangle>>
    spritesheetSourceBounds() noexcept
{
    return {
        {"background", {0, 3946, 3024, 1815}},
        {"ground", {1230, 1096, 3055, 270}},
        {"topSpike", {3458, 2910, 409, 902}},
        {"bottomSpike", {1493, 2910, 409, 902}},
        {"plane", {18, 2116, 331, 275}},
        {"getReady", {3408, 361, 1513, 273}},
        {"gameOver", {3408, 714, 1557, 294}},
        {"cursorNormal", {433, 2547, 146, 149}},
        {"cursorPressed", {55, 2474, 223, 222}}
    };
}

Spritesheet& Spritesheet::instance()
{
    static Spritesheet spritesheet;
    return spritesheet;
}

const Texture& Spritesheet::texture() const noexcept
{
    return mTexture;
}

const Rectangle& Spritesheet::sourceBounds(const std::string& key) const
{
    const auto iter = std::find_if(cbegin(mSourceBounds), cend(mSourceBounds),
        [&key](const auto& elem) {
            return elem.first == key;
        });
    if (iter == cend(mSourceBounds)) {
        throw std::exception("invalid key");
    }
    return iter->second;
}

Spritesheet::Spritesheet()
    : mTexture(spritesheetTexture())
    , mSourceBounds(spritesheetSourceBounds())
{
}

} // namespace TappyPlane
