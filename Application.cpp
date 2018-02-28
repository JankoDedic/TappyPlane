#include "Application.hpp"

#include "Renderer.hpp"

namespace TappyPlane {

using namespace SDLW::Events;

Application::Application()
{
    run();
}

void Application::handleEvent(const Event& event)
{
    if (event.type() == Event::Type::Quit) {
        mIsRunning = false;
    } else {
        mGame.handleEvent(event);
        mCursor.handleEvent(event);
    }
}

void Application::update()
{
    mGame.update();
}

void Application::draw() const
{
    mGame.draw();
    mCursor.draw();
}

void Application::run()
{
    using namespace SDLW::Time;

    Event event;
    constexpr Clock::duration frameTime{16};
    auto lastUpdateTime = Clock::now();
    while (mIsRunning) {
        while (Queue::poll(event)) {
            handleEvent(event);
        }
        if (Clock::now() > lastUpdateTime + frameTime) {
            update();
            Renderer::instance().clear();
            draw();
            Renderer::instance().present();
            lastUpdateTime = Clock::now();
        }
    }
}

} // namespace TappyPlane
