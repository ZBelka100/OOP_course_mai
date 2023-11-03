#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <algorithm>
#include <memory>

template <Number X, Number Y>
class Triangle : public Figure<X,Y> {
using Figure<X,Y>::vertices;
using Figure<X,Y>::_size;
using Figure<X,Y>::findCenter;
public:
    Triangle();
    Triangle(point<X,Y> p1, point<X,Y> p2, point<X,Y> p3);

    bool isThisFigure();
    std::string draw() const override;
    operator double();
};

#include "triangle.hpp"