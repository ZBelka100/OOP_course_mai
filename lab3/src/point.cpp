#include "../header/point.h"


    std::istream& operator>>(std::istream& in, point& point) {
        in >> point.x >> point.y;
        return in;
    }


    std::ostream& operator<<(std::ostream& out, const point& point) {
        out << point.x << ' ' << point.y << ' ';
        return out;
    }

    bool point::operator==(point& other) {
        return (x - other.x < 0.00001 && x - other.x > -0.00001)  && (y - other.y < 0.00001 && y - other.y > -0.00001) ;
    }


bool point::operator<(point& other) {
    if (x < other.x) {
        return true;
    } else if (x == other.x) {
        return y < other.y;
    }
    return false;
}

long double Distance(point &a, point &b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool comparePoints(point& p1, point& p2) {
    if (p1.x - p2.x < 0.00001 && p1.x - p2.x > -0.00001) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}
bool comparePointsY(point& p1, point& p2) {
    return p1.y > p2.y;
}

bool compareClockwise(point& center,point& a, point& b) {
    long double angleA = atan2(a.y - center.y, a.x - center.x);
    long double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}