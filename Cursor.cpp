#include "Cursor.hpp"

#include "Renderer.hpp"
#include "Spritesheet.hpp"

namespace TappyPlane {

using namespace SDLW::Video;
using namespace SDLW::Events;

constexpr Size normalCursorSize{146, 149};
constexpr Size pressedCursorSize{223, 222};

Cursor::Cursor()
    : mNormalSourceBounds(Spritesheet::instance().sourceBounds("cursorNormal"))
    , mPressedSourceBounds(
        Spritesheet::instance().sourceBounds("cursorPressed"))
    , mNormalSize(normalCursorSize)
    , mPressedSize(pressedCursorSize)
{
    Mouse::ActiveCursor::hide();
}

void Cursor::handleEvent(const Event& event)
{
    switch (event.type()) {
    case Event::Type::MouseButtonDown:
        mIsPressed = true;
        break;
    case Event::Type::MouseButtonUp:
        mIsPressed = false;
        break;
    case Event::Type::MouseMotion:
        mPosition = {event.mouseMotionEvent().x(),
            event.mouseMotionEvent().y()};
        break;
    default:
        break;
    }
}

void Cursor::draw() const
{
    if (mIsPressed) {
        auto position = mPosition;
        position.setX(position.x() - mNormalSize.width() / 2);
        position.setY(position.y() - mNormalSize.height() / 2);
        Renderer::instance().copy(Spritesheet::instance().texture(),
            mPressedSourceBounds, Rectangle{position, mPressedSize});
    } else {
        Renderer::instance().copy(Spritesheet::instance().texture(),
            mNormalSourceBounds, Rectangle{mPosition, mNormalSize});
    }
}

} // namespace TappyPlane
