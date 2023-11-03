#include "../header/point.h"

template <Number X, Number Y>
    std::istream& operator>>(std::istream& in, point<X, Y>& point) {
        in >> point.x >> point.y;
        return in;
    }

template <Number X, Number Y>
    std::ostream& operator<<(std::ostream& out, const point<X, Y>& point) {
        out << point.x << ' ' << point.y << ' ';
        return out;
    }

template <Number X, Number Y>
    bool point<X, Y>::operator==(point<X, Y>& other) {
        return (x - other.x < 0.00001 && x - other.x > -0.00001)  && (y - other.y < 0.00001 && y - other.y > -0.00001) ;
    }

template <Number X, Number Y>
bool point<X, Y>::operator<(point<X, Y>& other) {
    if (x < other.x) {
        return true;
    } else if (x == other.x) {
        return y < other.y;
    }
    return false;
}

template <Number X, Number Y>
long double Distance(point<X, Y> &a, point<X, Y> &b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
template <Number X, Number Y>
bool comparePoints(point<X, Y>& p1, point<X, Y>& p2) {
    if (p1.x - p2.x < 0.00001 && p1.x - p2.x > -0.00001) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}
template <Number X, Number Y>
bool comparePointsY(point<X, Y>& p1, point<X, Y>& p2) {
    return p1.y > p2.y;
}
template <Number X, Number Y>
bool compareClockwise(point<X, Y>& center,point<X, Y>& a, point<X, Y>& b) {
    long double angleA = atan2(a.y - center.y, a.x - center.x);
    long double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}