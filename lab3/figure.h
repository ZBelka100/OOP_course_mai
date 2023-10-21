#pragma once

#include "point.h"
#include <iostream>
#include <algorithm>
#include <string>

class Figure {
protected:
    point* vertices;
    int _size;
    char tag;

public:
    Figure();
    Figure(int n, char t);
    virtual point findCenter() const;
    virtual bool isThisFigure();
    virtual std::string draw() const;
    virtual operator double() const;
    
    friend std::istream& operator>>(std::istream& in, Figure& figure);
    friend std::ostream& operator<<(std::ostream& out, const Figure& figure);
    
    bool operator==(const Figure& other) const;
    Figure& operator=(Figure& other);
    Figure& operator=(Figure&& other) noexcept;
    
    virtual ~Figure() noexcept;
};

