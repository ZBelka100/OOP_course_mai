#include "../header/figure.h"
#include "../header/array.h"
#include "../header/triangle.h"
#include "../header/rectangle.h"
#include "../header/square.h"

int main() {
    DynamicArray<std::shared_ptr<Figure<int, int>>> arr;
    std::shared_ptr<Figure<int, int>> figure1 = std::make_shared<Triangle<int, int>>();
    std::shared_ptr<Figure<int, int>> figure2 = std::make_shared<Rectangle<int, int>>();
    std::shared_ptr<Figure<int, int>> figure3 = std::make_shared<Square<int, int>>();
    std::cin >> *figure1 >> *figure2 >> *figure3;
    arr.pushBack(figure1);
    arr.pushBack(figure2);
    arr.pushBack(figure3);
    findAllCenters(arr);
    findAllAreas(arr);
    std::cout  << '\n' << findSumAreas(arr);
    return 0;
}
