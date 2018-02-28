#include "Game.hpp"

#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace TappyPlane {

using namespace SDLW::Video;
using namespace SDLW::Events;

constexpr auto backgroundSpritesheetHandle = "background";
constexpr auto backgroundBounds = canvasBounds;
constexpr auto backgroundScrollSpeed = 0.5f;

constexpr auto groundSpritesheetHandle = "ground";
constexpr Rectangle groundBounds{0, canvasBounds.height() - 270,
    canvasBounds.width(), 270};
constexpr auto groundScrollSpeed = 2.0f;

constexpr int spikePairDistance{420};
constexpr int spikesScrollSpeed{5};

constexpr auto getReadySpritesheetHandle = "getReady";
constexpr Rectangle getReadyBounds{canvasBounds.width() / 2 - 907 / 2,
    canvasBounds.height() / 2 - 163 / 2, 907, 163};

constexpr auto gameOverSpritesheetHandle = "gameOver";
constexpr Rectangle gameOverBounds{canvasBounds.width() / 2 - 934 / 2,
    canvasBounds.height() / 2 - 176 / 2, 934, 176};

Game::Game()
    : mGameState(State::GetReady)
    , mBackground(backgroundSpritesheetHandle, backgroundBounds,
        backgroundScrollSpeed)
    , mGround(groundSpritesheetHandle, groundBounds, groundScrollSpeed)
    , mSpikes(spikePairDistance, spikesScrollSpeed)
    , mGetReadySprite(getReadySpritesheetHandle, getReadyBounds)
    , mGameOverSprite(gameOverSpritesheetHandle, gameOverBounds)
{
}

void Game::handleEvent(const Event& event) noexcept
{
    if (event.type() == Event::Type::MouseButtonDown) {
        switch (mGameState) {
        case State::GetReady:
            start();
            break;
        case State::InProgress:
            mPlane.jump();
            break;
        case State::GameOver:
            reset();
            break;
        default:
            break;
        }
    }
}

void Game::update() noexcept
{
    if (mGameState != State::InProgress) {
        return;
    }
    mBackground.update();
    mGround.update();
    mSpikes.update();
    mPlane.update();
    if (hasPlaneCrashed()) {
        mBackground.pause();
        mGround.pause();
        mSpikes.pause();
        mPlane.pause();
        mGameState = State::GameOver;
    }
}

void Game::draw() const
{
    mBackground.draw();
    mPlane.draw();
    mSpikes.draw();
    mGround.draw();
    if (mGameState == State::GetReady) {
        mGetReadySprite.draw();
    } else if (mGameState == State::GameOver) {
        mGameOverSprite.draw();
    }
}

void Game::start()
{
    mBackground.play();
    mSpikes.play();
    mGround.play();
    mPlane.play();
    mGameState = State::InProgress;
}

void Game::reset()
{
    mPlane.reset();
    mSpikes.reset();
    mGameState = State::GetReady;
}

static bool areColliding(const Plane& plane, const Spikes& spikes)
{
    for (auto[first, last] = spikes.bounds(); first < last; ++first) {
        if (areIntersecting(plane.bounds(), first->topSpikeBounds)
            || areIntersecting(plane.bounds(), first->bottomSpikeBounds)) {
            return true;
        }
    }
    return false;
}

bool Game::hasPlaneCrashed()
{
    return areColliding(mPlane, mSpikes) || didPlaneHitTheGround()
        || didPlaneHitTheCeiling();
}

bool Game::didPlaneHitTheGround()
{
    return areIntersecting(mPlane.bounds(), mGround.bounds());
}

bool Game::didPlaneHitTheCeiling()
{
    return topOf(mPlane.bounds()) < topOf(canvasBounds);
}

} // namespace TappyPlane
