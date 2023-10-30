#pragma once

#include "figure.h"
#include <iostream>

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3, long double x4, long double y4);
    Rectangle(point p1, point p2, point p3, point p4);

    bool isThisFigure() override;
    std::string draw() const override;
    operator double() const;
};