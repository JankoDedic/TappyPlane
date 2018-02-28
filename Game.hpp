#pragma once

#include "InfiniteSideScrollingSprite.hpp"
#include "Plane.hpp"
#include "Spikes.hpp"
#include "Sprite.hpp"

namespace TappyPlane {

class Game {
public:
    Game();

    void handleEvent(const SDLW::Events::Event&) noexcept;

    void update() noexcept;

    void draw() const;

private:
    enum class State {
        GetReady, InProgress, GameOver
    };

    void start();

    void reset();

    bool hasPlaneCrashed();

    bool didPlaneHitTheGround();

    bool didPlaneHitTheCeiling();

    State mGameState;
    InfiniteSideScrollingSprite mBackground;
    InfiniteSideScrollingSprite mGround;
    Spikes mSpikes;
    Plane mPlane;
    Sprite mGetReadySprite;
    Sprite mGameOverSprite;
};

} // namespace TappyPlane
