#pragma once

#include <cmath>
#include <iostream>

class point {
    public:
    long double x;
    long double y;

    friend std::istream& operator>>(std::istream& in, point& point);
    friend std::ostream& operator<<(std::ostream& out, const point& point);
    bool operator==(point& other);
    bool operator<(point& other);
};
    long double Distance(point &a, point &b);
    bool comparePoints(point& p1, point& p2);
    bool comparePointsY(point& p1, point& p2);
    bool compareClockwise(point& center, point& a, point& b) ;
