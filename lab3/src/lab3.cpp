#include "../header/all.h"

int main() {

    figureArray arr;
    Triangle figure1;
    Rectangle figure2;
    Square figure3;
    std::cin >> figure1 >> figure2 >> figure3;
    arr.pushBack(&figure1);
    arr.pushBack(&figure2);
    arr.pushBack(&figure3);
    arr.findAllAreas();
    arr.findAllCenters();
    std::cout << arr << '\n';
    return 0;
}
