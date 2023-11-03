#pragma once

#include <cmath>
#include <iostream>
#include <concepts>
#include <memory>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number X, Number Y>
class point {
    public:
    X x;
    Y y;
    point() = default;
    point(const X& x, const Y& y) : x(x), y(y) {}
    template <Number _X, Number _Y>
    friend std::istream& operator>>(std::istream& in, point<_X,_Y>& point);
    template <Number X_, Number Y_>
    friend std::ostream& operator<<(std::ostream& out, const point<X_,Y_>& point);
    bool operator==(point& other);
    bool operator<(point& other);
};
template <Number X, Number Y>
long double Distance(point<X, Y> &a, point<X, Y> &b);
template <Number X, Number Y>
bool comparePoints(point<X, Y>& p1, point<X, Y>& p2);
template <Number X, Number Y>
bool comparePointsY(point<X, Y>& p1, point<X, Y>& p2);
template <Number X, Number Y>
bool compareClockwise(point<X, Y>& center, point<X, Y>& a, point<X, Y>& b) ;

#include "point.hpp"