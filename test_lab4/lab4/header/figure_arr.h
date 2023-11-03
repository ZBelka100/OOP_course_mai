#pragma once

#include <string>
#include <iostream>
#include "figure.h"
#include "point.h"
#include <concepts>
#include <memory>

template <Number X, Number Y>
class figureArray {
public:
    figureArray();
    ~figureArray();

    int getSize() const;
    void findAllCenters();
    void findAllAreas();
    double findSumAreas();

    void remove(int index);
    void pushBack(std::shared_ptr<Figure<X,Y>> figure);
    template <Number _X, Number _Y>
    friend std::ostream& operator<<(std::ostream &stream, const figureArray<_X,_Y>&  collection);

private:
    std::shared_ptr<Figure<X,Y>>* figures;
    int capacity;
    int size;
};

#include "figure_arr.hpp"