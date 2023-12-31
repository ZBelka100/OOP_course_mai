
template <Number X, Number Y>
    Rectangle<X,Y>::Rectangle() : Figure<X,Y>(4) { 
    }
template <Number X, Number Y>
    bool Rectangle<X,Y>::isThisFigure() {
        point center = findCenter();
        std::sort(vertices.begin(), vertices.end(), [&center](point<X,Y>& a, point<X,Y>& b) {return compareClockwise(center, a, b);});
        for (int i = 0; i < _size - 1; ++i) {
            if (vertices[i] == vertices[i+1]) {
                throw std::invalid_argument("Это похоже на вырожденную фигуру");
            }
        }
        // Проверяем длины сторон (параллельность и равенство)
        long double side[_size];
        for (int i = 0; i < _size; ++i) {
            side[i] = sqrt(pow(vertices[i].x - vertices[(i+1)%_size].x, 2) + pow(vertices[i].y - vertices[(i+1)%_size].y, 2));
        }
        if (side[0] != side[2] || side[1] != side[3]) {
            return false;
        }

        // Проверяем углы (90 градусов)
        long double dotProduct[_size];
        for (int i = 0; i < _size; ++i) {
            dotProduct[i] = (vertices[(i+1)%_size].x - vertices[i].x) * (vertices[(i+2)%_size].x - vertices[(i+1)%_size].x) 
            + (vertices[(i+1)%_size].y - vertices[i].y) * (vertices[(i+2)%_size].y - vertices[(i+1)%_size].y);
        }
        if (dotProduct[0] == 0 && dotProduct[1] == 0 && dotProduct[2] == 0 && dotProduct[3] == 0) {
            return true;
        }
        return false;
    }
template <Number X, Number Y>
   Rectangle<X,Y>:: Rectangle(point<X,Y> p1, point<X,Y> p2, point<X,Y> p3, point<X,Y> p4) : Figure<X,Y>(4) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
        if (!isThisFigure()) {
            _size = 0;
            throw std::invalid_argument("Это не прямоугольник");
        }
    }
template <Number X, Number Y>
    std::string Rectangle<X,Y>::draw() const  {
        return "This is a rectangle.";
    }
template <Number X, Number Y>
    Rectangle<X,Y>::operator double() {
        long double d1 = Distance(vertices[0], vertices[1]), d2 = Distance(vertices[0], vertices[2]), d3 = Distance(vertices[0], vertices[3]); 
        long double ma = std::max(d1, std::max(d2, d3)), mi = std::min(d1, std::min(d2, d3));
        return (mi * (d1+d2+d3-mi-ma));
    }
