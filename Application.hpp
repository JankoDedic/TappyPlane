#pragma once

#include "Cursor.hpp"
#include "Game.hpp"

namespace TappyPlane {

class Application {
public:
    Application();

private:
    void handleEvent(const SDLW::Events::Event&);

    void update();

    void draw() const;

    void run();

    bool mIsRunning = true;
    Game mGame;
    Cursor mCursor;
};

} // namespace TappyPlane
