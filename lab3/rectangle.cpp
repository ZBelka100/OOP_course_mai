#include "rectangle.h"
#include "point.h"

    Rectangle::Rectangle() : Figure(4, 'r') { 
    }

    bool Rectangle::isThisFigure() {
        point center = findCenter();
        std::sort(vertices, vertices + _size, [&center](point& a, point& b) {return compareClockwise(center, a, b);});
        for (int i = 0; i < _size - 1; ++i) {
            if (vertices[i] == vertices[i+1]) {
                throw std::invalid_argument("Это похоже на вырожденную фигуру");
            }
        }
        // Проверяем длины сторон (параллельность и равенство)
        long double side1 = sqrt(pow(vertices[0].x - vertices[1].x, 2) + pow(vertices[0].y - vertices[1].y, 2));
        long double side2 = sqrt(pow(vertices[1].x - vertices[2].x, 2) + pow(vertices[1].y - vertices[2].y, 2));
        long double side3 = sqrt(pow(vertices[2].x - vertices[3].x, 2) + pow(vertices[2].y - vertices[3].y, 2));
        long double side4 = sqrt(pow(vertices[3].x - vertices[0].x, 2) + pow(vertices[3].y - vertices[0].y, 2));

        if (side1 != side3 || side2 != side4) {
            return false;
        }

        // Проверяем углы (90 градусов)
        long double dotProduct1 = (vertices[1].x - vertices[0].x) * (vertices[2].x - vertices[1].x) + (vertices[1].y - vertices[0].y) * (vertices[2].y - vertices[1].y);
        long double dotProduct2 = (vertices[2].x - vertices[1].x) * (vertices[3].x - vertices[2].x) + (vertices[2].y - vertices[1].y) * (vertices[3].y - vertices[2].y);
        long double dotProduct3 = (vertices[3].x - vertices[2].x) * (vertices[0].x - vertices[3].x) + (vertices[3].y - vertices[2].y) * (vertices[0].y - vertices[3].y);
        long double dotProduct4 = (vertices[0].x - vertices[3].x) * (vertices[1].x - vertices[0].x) + (vertices[0].y - vertices[3].y) * (vertices[1].y - vertices[0].y);

        if (dotProduct1 == 0 && dotProduct2 == 0 && dotProduct3 == 0 && dotProduct4 == 0) {
            return true;
        }
        return false;
    }

    Rectangle::Rectangle(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3, long double x4, long double y4) : Figure(4, 'r') {
        point p1 = {x1, y1}, p2 = {x2, y2}, p3 = {x3, y3}, p4 = {x4, y4};
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
       if (!isThisFigure()) {
            delete[] vertices;
            _size = 0;
            vertices = nullptr;
            throw std::invalid_argument("Это не прямоугольник");
        }
    }

   Rectangle:: Rectangle(point p1, point p2, point p3, point p4) : Figure(4, 'r') {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        if (!isThisFigure()) {
            delete[] vertices;
            _size = 0;
            vertices = nullptr;
            throw std::invalid_argument("Это не прямоугольник");
        }
    }

    std::string Rectangle::draw() const  {
        return "This is a rectangle.";
    }

    Rectangle::operator double() const{//маленький на средний
        long double d1 = Distance(vertices[0], vertices[1]), d2 = Distance(vertices[0], vertices[2]), d3 = Distance(vertices[0], vertices[3]); 
        long double ma = std::max(d1, std::max(d2, d3)), mi = std::min(d1, std::min(d2, d3));
        return (mi * (d1+d2+d3-mi-ma));
    }
