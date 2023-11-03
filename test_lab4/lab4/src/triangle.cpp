#include "../header/triangle.h"

template <Number X, Number Y>
    Triangle<X,Y>::Triangle() :  Figure<X,Y>(3) { 
    }
template <Number X, Number Y>
    bool Triangle<X,Y>::isThisFigure() {
        for (int i = 0; i < _size - 1; ++i) {
            if (vertices[i] == vertices[i+1]) {
                throw std::invalid_argument("Это похоже на вырожденную фигуру");
            }
        }
    }
template <Number X, Number Y>
    Triangle<X,Y>::Triangle(point<X,Y> p1, point<X,Y> p2, point<X,Y> p3) : Figure<X,Y>(3) {//?????
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        std::sort(vertices, vertices + _size, comparePoints);
        isThisFigure();
    }    
template <Number X, Number Y>
    std::string Triangle<X,Y>::draw() const {
        return "This is a triangle.";
    }
template <Number X, Number Y>
    Triangle<X,Y>::operator double() const{
        return abs((vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y)))/(double)2;
    }

