#include "RectangleFunctions.hpp"

namespace TappyPlane {

std::pair<SDLW::Video::Rectangle, SDLW::Video::Rectangle>
    horizontalSplit(const float splitPoint,
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    SDLW_ASSERT(0.0f <= splitPoint); SDLW_ASSERT(splitPoint <= 1.0f);
    SDLW::Video::Rectangle r1{rectangle.x(), rectangle.y(), rectangle.x() +
        int(splitPoint * rectangle.width()), rectangle.height()};
    SDLW::Video::Rectangle r2{r1.x() + r1.width(), rectangle.y(),
        rectangle.width() - r1.width(), rectangle.height()};
    return {r1, r2};
}

std::pair<SDLW::Video::Rectangle, SDLW::Video::Rectangle> verticalSplit(
    const float splitPoint, const SDLW::Video::Rectangle& rectangle) noexcept
{
    SDLW_ASSERT(0.0f <= splitPoint); SDLW_ASSERT(splitPoint <= 1.0f);
    SDLW::Video::Rectangle r1{rectangle.x(), rectangle.y(),
        rectangle.width(), rectangle.y() + int(splitPoint
        * rectangle.height())};
    SDLW::Video::Rectangle r2{rectangle.x(), r1.y() + r1.height(),
        rectangle.width(), rectangle.height() - r1.height()};
    return {r1, r2};
}

SDLW::Video::Rectangle horizontalSlice(const int leftX, const int rightX,
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    SDLW_ASSERT(rectangle.x() <= leftX);
    SDLW_ASSERT(leftX <= rectangle.x() + rectangle.width());
    SDLW_ASSERT(rectangle.x() <= rightX);
    SDLW_ASSERT(rightX <= rectangle.x() + rectangle.width());
    SDLW_ASSERT(leftX <= rightX);
    return {leftX, rectangle.y(), rightX - leftX, rectangle.height()};
}

} // namespace TappyPlane
