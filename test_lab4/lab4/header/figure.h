#pragma once

#include "point.h"
#include "array.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <memory>


//остались тесты и функции для приколов

template <Number X, Number Y>
class Figure {
protected:
    DynamicArray<point<X, Y>> vertices;
    int _size;

public:
    Figure();
    Figure(int n);
    virtual point<X, Y> findCenter();
    virtual bool isThisFigure();
    virtual std::string draw() const;
    virtual operator double() ;
    template <Number _X, Number _Y>
    friend std::istream& operator>>(std::istream& in, Figure<_X,_Y>& figure);
    template <Number X_, Number Y_>
    friend std::ostream& operator<<(std::ostream& out, Figure<X_,Y_>& figure);
    
    bool operator==(Figure<X,Y>& other);
    Figure<X,Y>& operator=(Figure<X,Y>& other);
    Figure<X,Y>& operator=(Figure<X,Y>&& other) noexcept;
    
    virtual ~Figure() noexcept;
};

#include "figure.hpp"