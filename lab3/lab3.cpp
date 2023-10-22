#include "all.h"

int main() {
    figureArray arr;
    Figure* figure1 = new Triangle({0, 0}, {2, 0}, {0, 3});
    Figure* figure2 = new Square ({0, 0}, {2, 0}, {0, 2}, {2, 2});
    Figure* figure3 = new Rectangle ({0, 0}, {1, 0}, {0, 2}, {1, 2});
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);
   // std::cout.rdbuf(capturedOutput.rdbuf());
    arr.findAllAreas();
    Rectangle rectangle({0, 0}, {-2, 0}, {0, -3}, {-2, -3});
    std::cout << double(rectangle);
    return 0;
}
