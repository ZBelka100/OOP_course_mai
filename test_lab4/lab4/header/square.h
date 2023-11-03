#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <algorithm>
#include <memory>

template <Number X, Number Y>
class Square : public Figure<X,Y> {
using Figure<X,Y>::vertices;
using Figure<X,Y>::_size;
using Figure<X,Y>::findCenter;
public:
    Square();
    Square(point<X,Y> p1, point<X,Y> p2, point<X,Y> p3, point<X,Y> p4);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() ;
};

#include "square.hpp"

