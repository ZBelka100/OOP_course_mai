#pragma once

#include "figure.h"
#include "point.h"
#include <iostream>
#include <algorithm>

class Triangle : public Figure {
public:
    Triangle();
    Triangle(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3);
    Triangle(point p1, point p2, point p3);

    bool isThisFigure();
    std::string draw() const override;
    operator double() const;
};
