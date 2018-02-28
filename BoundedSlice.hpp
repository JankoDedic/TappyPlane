#pragma once

#include "SDLW.hpp"

namespace TappyPlane {

template<class T>
T wrap(T value, T min, T max) noexcept;

template<class T>
class BoundedSlice {
public:
    BoundedSlice(T leftBound, T rightBound, T length) noexcept;

    BoundedSlice(const BoundedSlice&) = delete;

    BoundedSlice(BoundedSlice&&) = delete;

    BoundedSlice& operator=(const BoundedSlice&) = delete;

    BoundedSlice& operator=(BoundedSlice&&) = delete;

    void operator+=(T) noexcept;

    void operator-=(T) noexcept;

    T leftBound() const noexcept;

    T rightBound() const noexcept;

    T length() const noexcept;

    T leftEnd() const noexcept;

    T rightEnd() const noexcept;

    bool isWrapped() const noexcept;

    T leftPieceLength() const noexcept;

    T rightPieceLength() const noexcept;

private:
    T mLeftEnd;
    T mRightEnd;
    T mLeftBound;
    T mRightBound;
};

template<class T>
T wrap(const T value, const T min, const T max) noexcept
{
    if (value < min) {
        const auto minMaxDifference = max - min;
        const auto difference = min - value;
        return max - (int(difference) % int(minMaxDifference));
    } else if (value > max) {
        const auto minMaxDifference = max - min;
        const auto difference = value - max;
        return min + (int(difference) % int(minMaxDifference));
    }
    return value;
}

template<class T>
BoundedSlice<T>::BoundedSlice(const T leftBound, const T rightBound,
    const T length) noexcept
    : mLeftBound(leftBound)
    , mRightBound(rightBound)
{
    SDLW_ASSERT(leftBound <= rightBound);
    SDLW_ASSERT(length <= rightBound - leftBound);
    mLeftEnd = mLeftBound;
    mRightEnd = mLeftBound + length;
}

template<class T>
void BoundedSlice<T>::operator+=(const T value) noexcept
{
    mLeftEnd = wrap(mLeftEnd + value, mLeftBound, mRightBound);
    mRightEnd = wrap(mRightEnd + value, mLeftBound, mRightBound);
}

template<class T>
void BoundedSlice<T>::operator-=(const T value) noexcept
{
    mLeftEnd = wrap(mLeftEnd - value, mLeftBound, mRightBound);
    mRightEnd = wrap(mRightEnd - value, mLeftBound, mRightBound);
}

template<class T>
T BoundedSlice<T>::leftBound() const noexcept
{
    return mLeftBound;
}

template<class T>
T BoundedSlice<T>::rightBound() const noexcept
{
    return mRightBound;
}

template<class T>
T BoundedSlice<T>::length() const noexcept
{
    if (isWrapped()) {
        return leftPieceLength() + rightPieceLength();
    }
    return mRightEnd - mLeftEnd;
}

template<class T>
T BoundedSlice<T>::leftEnd() const noexcept
{
    return mLeftEnd;
}

template<class T>
T BoundedSlice<T>::rightEnd() const noexcept
{
    return mRightEnd;
}

template<class T>
bool BoundedSlice<T>::isWrapped() const noexcept
{
    return mLeftEnd > mRightEnd;
}

template<class T>
T BoundedSlice<T>::leftPieceLength() const noexcept
{
    SDLW_ASSERT(isWrapped());
    return mRightEnd - mLeftBound;
}

template<class T>
T BoundedSlice<T>::rightPieceLength() const noexcept
{
    SDLW_ASSERT(isWrapped());
    return mRightBound - mLeftEnd;
}

} // namespace TappyPlane
