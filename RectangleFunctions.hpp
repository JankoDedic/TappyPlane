#pragma once

#include <stdexcept>

#include "SDLW.hpp"

namespace TappyPlane {

constexpr void scale(SDLW::Video::Size& size, double factor);

constexpr void scaleToFit(SDLW::Video::Size& source,
    const SDLW::Video::Size& destination);

constexpr SDLW::Video::Rectangle fittingRectangle(SDLW::Video::Size source,
    const SDLW::Video::Rectangle& destination);

constexpr void scale(SDLW::Video::Rectangle& rectangle, double scaleFactor);

constexpr void scaleInPlace(SDLW::Video::Rectangle& rectangle,
    double scaleFactor);

constexpr SDLW::Video::Point topLeftPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point topPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point topRightPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point leftPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point centerPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point rightPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point bottomLeftPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point bottomPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr SDLW::Video::Point bottomRightPointOf(const SDLW::Video::Rectangle&)
    noexcept;

constexpr int leftOf(const SDLW::Video::Rectangle&) noexcept;

constexpr int rightOf(const SDLW::Video::Rectangle&) noexcept;

constexpr int topOf(const SDLW::Video::Rectangle&) noexcept;

constexpr int bottomOf(const SDLW::Video::Rectangle&) noexcept;

std::pair<SDLW::Video::Rectangle, SDLW::Video::Rectangle> horizontalSplit(
    float splitPoint, const SDLW::Video::Rectangle&) noexcept;

std::pair<SDLW::Video::Rectangle, SDLW::Video::Rectangle> verticalSplit(
    float splitPoint, const SDLW::Video::Rectangle&) noexcept;

SDLW::Video::Rectangle horizontalSlice(int leftX, int rightX,
    const SDLW::Video::Rectangle&) noexcept;

constexpr void scale(SDLW::Video::Size& size, const double factor)
{
    if (factor < 0) {
        throw std::domain_error("negative factor");
    }
    size.setWidth(int(size.width() * factor));
    size.setHeight(int(size.height() * factor));
}

constexpr void scaleToFit(SDLW::Video::Size& source,
    const SDLW::Video::Size& destination)
{
    auto factor = double(destination.width()) / source.width();
    if (factor * source.height() > destination.height()) {
        factor = double(destination.height()) / source.height();
    }
    scale(source, factor);
}

constexpr SDLW::Video::Rectangle fittingRectangle(SDLW::Video::Size size,
    const SDLW::Video::Rectangle& destination)
{
    scaleToFit(size, destination.size());
    return SDLW::Video::Rectangle(
        destination.x() + (destination.width() - size.width()) / 2,
        destination.y() + (destination.height() - size.height()) / 2, size);
}

constexpr void scale(SDLW::Video::Rectangle& rectangle,
    const double scaleFactor)
{
    if (scaleFactor < 0) {
        throw std::domain_error("negative scale factor");
    }
    rectangle.setWidth(int(rectangle.width() * scaleFactor));
    rectangle.setHeight(int(rectangle.height() * scaleFactor));
}

constexpr void scaleInPlace(SDLW::Video::Rectangle& rectangle,
    const double scaleFactor)
{
    const auto oldSize = rectangle.size();
    scale(rectangle, scaleFactor);
    rectangle.setX(rectangle.x() + (oldSize.width() - rectangle.width()) / 2);
    rectangle.setY(rectangle.y() + (oldSize.height() - rectangle.height()) / 2);
}

constexpr SDLW::Video::Point topLeftPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return rectangle.position();
}

constexpr SDLW::Video::Point topPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width() / 2, rectangle.y()};
}

constexpr SDLW::Video::Point topRightPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width(), rectangle.y()};
}

constexpr SDLW::Video::Point leftPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x(), rectangle.y() + rectangle.height() / 2};
}

constexpr SDLW::Video::Point centerPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width() / 2,
        rectangle.y() + rectangle.height() / 2};
}

constexpr SDLW::Video::Point rightPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width(),
        rectangle.y() + rectangle.height() / 2};
}

constexpr SDLW::Video::Point bottomLeftPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x(), rectangle.y() + rectangle.height()};
}

constexpr SDLW::Video::Point bottomPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width() / 2,
        rectangle.y() + rectangle.height()};
}

constexpr SDLW::Video::Point bottomRightPointOf(
    const SDLW::Video::Rectangle& rectangle) noexcept
{
    return {rectangle.x() + rectangle.width(),
        rectangle.y() + rectangle.height()};
}

constexpr int leftOf(const SDLW::Video::Rectangle& rectangle) noexcept
{
    return rectangle.x();
}

constexpr int rightOf(const SDLW::Video::Rectangle& rectangle) noexcept
{
    return rectangle.x() + rectangle.width();
}

constexpr int topOf(const SDLW::Video::Rectangle& rectangle) noexcept
{
    return rectangle.y();
}

constexpr int bottomOf(const SDLW::Video::Rectangle& rectangle) noexcept
{
    return rectangle.y() + rectangle.height();
}

} // namespace TappyPlane
