#include "all.h"

int main() {
    Rectangle rectangle({0, 0}, {-2, 0}, {0, -3}, {-2, -3});
    point p = {-1, -1.5};
    std::cout << rectangle.findCenter() << ' ' << p << '\n';
    Square square({0, 0}, {-3, 0}, {0, -3}, {-3, -3});
    p = {-1.5, -1.5};
    std::cout << square.findCenter() << ' ' << p << '\n';
    Triangle triangle({0, 0}, {-3, 0}, {0, -3});
    p = {-1, -1};
    std::cout << triangle.findCenter() << ' ' << p << '\n';
    return 0;
}
