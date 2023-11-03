#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <memory>

template <Number X, Number Y>
class Rectangle : public Figure<X,Y> {
using Figure<X,Y>::vertices;
using Figure<X,Y>::_size;
using Figure<X,Y>::findCenter;
public:
    Rectangle();
    Rectangle(point<X,Y> p1, point<X,Y> p2, point<X,Y> p3, point<X,Y> p4);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() ;
};

#include "rectangle.hpp"