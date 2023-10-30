#include "../header/triangle.h"
#include "../header/point.h"

    Triangle::Triangle() :  Figure(3, 't') { 
    }

    bool Triangle::isThisFigure() {
        for (int i = 0; i < _size - 1; ++i) {
            if (vertices[i] == vertices[i+1]) {
                throw std::invalid_argument("Это похоже на вырожденную фигуру");
            }
        }
    }

    Triangle::Triangle(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3) : Figure(3, 't') { //любое
        vertices[0] = {x1, y1};
        vertices[1] = {x2, y2};
        vertices[2] = {x3, y3};
        std::sort(vertices, vertices + _size, comparePoints);
        isThisFigure();

    }

    Triangle::Triangle(point p1, point p2, point p3) : Figure(3, 't') {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        std::sort(vertices, vertices + _size, comparePoints);
        isThisFigure();
    }    

    std::string Triangle::draw() const {
        return "This is a triangle.";
    }

    Triangle::operator double() const{
        return abs((vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y)))/(double)2;
    }

