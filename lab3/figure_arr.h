#pragma once

#include <string>
#include <iostream>
#include "figure.h"
#include "point.h"

class figureArray {
public:
    figureArray();
    ~figureArray();

    int getSize();
    void findAllCenters();
    void findAllAreas();
    double findSumAreas();

    void remove(int index);
    void pushBack(Figure* figure);

    friend std::ostream& operator<<(std::ostream &stream, const figureArray&  collection);

private:
    Figure** figures;
    int capacity;
    int size;
};