#pragma once

#include "SDLW.hpp"

template<class T>
T wrap(T value, T min, T max) noexcept;

// Required operations:
//  1. All comparison operations
//  2. Assignment: (=), +=, -=, *=, /= and %= if std::is_integral<T>
//  3. Increment/decrement: ++a, --a, (a++, a--)
template<class T>
class Bounded {
public:
    explicit operator T() const noexcept;

    Bounded(T leftBound, T rightBound) noexcept;

    Bounded(const Bounded&) = delete;

    Bounded(Bounded&&) = delete;

    Bounded& operator=(const Bounded&) = delete;

    Bounded& operator=(Bounded&&) = delete;

    T value() const noexcept;

    T leftBound() const noexcept;

    T rightBound() const noexcept;

    void operator=(T) noexcept;

    void operator+=(T) noexcept;

    void operator-=(T) noexcept;

private:
    T mValue;
    T mLeftBound;
    T mRightBound;
};

template<class T>
Bounded<T>::operator T() const noexcept
{
    return mValue;
}

template<class T>
Bounded<T>::Bounded(const T leftBound, const T rightBound) noexcept
    : mLeftBound(leftBound)
    , mRightBound(rightBound)
    , mValue(mLeftBound)
{
    SDLW_ASSERT(leftBound <= rightBound);
}

template<class T>
T Bounded<T>::value() const noexcept
{
    return mValue;
}

template<class T>
T Bounded<T>::leftBound() const noexcept
{
    return mLeftBound;
}

template<class T>
T Bounded<T>::rightBound() const noexcept
{
    return mRightBound;
}

template<class T>
void Bounded<T>::operator=(const T value) noexcept
{
    mValue = wrap(value, mLeftBound, mRightBound);
}

template<class T>
void Bounded<T>::operator+=(const T value) noexcept
{
    mValue = wrap(mValue + value, mLeftBound, mRightBound);
}

template<class T>
void Bounded<T>::operator-=(const T value) noexcept
{
    mValue = wrap(mValue - value, mLeftBound, mRightBound);
}

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
class BoundedSlice {
public:
    BoundedSlice(T leftBound, T rightBound, T sliceLength) noexcept;

    BoundedSlice(const BoundedSlice&) = delete;

    BoundedSlice(BoundedSlice&&) = delete;

    BoundedSlice& operator=(const BoundedSlice&) = delete;

    BoundedSlice& operator=(BoundedSlice&&) = delete;

    void operator+=(T) noexcept;

    void operator-=(T) noexcept;

    T leftBound() const noexcept;

    T rightBound() const noexcept;

    T sliceLength() const noexcept;

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
BoundedSlice<T>::BoundedSlice(const T leftBound, const T rightBound,
    const T sliceLength) noexcept
    : mLeftBound(leftBound)
    , mRightBound(rightBound)
{
    SDLW_ASSERT(leftBound <= rightBound);
    SDLW_ASSERT(sliceLength <= rightBound - leftBound);
    mLeftEnd = mLeftBound;
    mRightEnd = mLeftBound + sliceLength;
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
T BoundedSlice<T>::sliceLength() const noexcept
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
