#include "square.h"
#include "point.h"

    Square::Square() : Figure(4, 's') { 
    }

    bool Square::isThisFigure() {
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

        if (side1 != side3 || side1 != side2 || side1 != side4) {
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

   Square::Square(long double x1, long double y1, long double x2, long double y2, long double x3, long double y3, long double x4, long double y4) : Figure(4, 's') {
        vertices[0] = {x1, y1};
        vertices[1] = {x2, y2};
        vertices[2] = {x3, y3};
        vertices[3] = {x4, y4};
        if (!isThisFigure()) {
            delete[] vertices;
            _size = 0;
            vertices = nullptr;
            throw std::invalid_argument("Это не квадрат");
        }
        
    }

    Square::operator double() const{
        return std::min(Distance(vertices[0], vertices[1]), Distance(vertices[0], vertices[2]))*std::min(Distance(vertices[0], vertices[1]), Distance(vertices[0], vertices[2]));
    }

    Square::Square(point p1, point p2, point p3, point p4) : Figure(4, 's'){
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        if (!isThisFigure()) {
            delete[] vertices;
            _size = 0;
            vertices = nullptr;
            throw std::invalid_argument("Это не квадрат");
        }
    }

    std::string Square::draw() const {
        return "This is a square.";
    }
