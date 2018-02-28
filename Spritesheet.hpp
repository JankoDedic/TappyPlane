#pragma once

#include <string>
#include <utility>
#include <vector>

#include "SDLW.hpp"

namespace TappyPlane {

class Spritesheet {
public:
    static Spritesheet& instance();

    const SDLW::Video::Texture& texture() const noexcept;

    const SDLW::Video::Rectangle& sourceBounds(const std::string& key) const;

private:
    Spritesheet();

    SDLW::Video::Texture mTexture;
    std::vector<std::pair<std::string, SDLW::Video::Rectangle>> mSourceBounds;
};

} // namespace TappyPlane
