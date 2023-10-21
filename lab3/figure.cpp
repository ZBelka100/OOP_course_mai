#include "point.h"
#include "figure.h"

    
    Figure::Figure() : vertices(nullptr), _size(0), tag('f') {};

    Figure::Figure(int n, char t = 'f') : tag(t){
        _size = n;
        vertices = new point[n];
    };
    point Figure::findCenter() const {
        point center = {0.0, 0.0};
        for (int i = 0; i < _size; ++i) {
            center.x += vertices[i].x;
            center.y += vertices[i].y;
        }
        center.x /= _size;
        center.y /= _size;
        return center;
    }

    bool Figure::isThisFigure() {
        return true;
    }

    std::string Figure::draw() const {
        return "This is a generic figure.";
    }

    Figure::operator double() const{
        return (vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y))/2;
    }

    std::istream& operator>>(std::istream& in, Figure& figure) {
        for (int i = 0; i < figure._size; ++i) {
            in >> figure.vertices[i].x >> figure.vertices[i].y;
        }
        if (figure.isThisFigure()) {
            return in;
        }
        throw std::invalid_argument("Ты что то перепутал");
    }


    std::ostream& operator<<(std::ostream& out, const Figure& figure) {
        for (int i = 0; i < figure._size; ++i) {
            out << "p" << i+1 << " = " << figure.vertices[i].x << ' ' << figure.vertices[i].y << "   ";
        }
        return out;
    } 

    bool Figure::operator==(const Figure& other) const {
        if (_size != other._size) {
            return false;
        }
        long double distances1[_size];
        long double distances2[_size];
        for (int i = 0; i < _size; ++i) {
            distances1[i] = Distance(vertices[i],vertices[(i+1)%_size]);
            distances2[i] = Distance(other.vertices[i],other.vertices[(i+1)%_size]);
        }
        std::sort(distances1, distances1 + _size);
        std::sort(distances2, distances2 + _size);
        for (int i = 0; i < _size; ++i) {
            if (!(distances1[i] == distances2[i])) {
                return false;
            }
        }
        return true;

    }

    Figure& Figure::operator=(Figure& other) {
        if (tag != other.tag) {
            throw std::underflow_error("Разные фигуры");
        }
        if (*this != other) {
            _size  = other._size;
            delete[] vertices;
            vertices = new point[_size];

            for(size_t i = 0; i < _size; ++i) {
                vertices[i] = other.vertices[i];
            }
        }    
        return *this;
    }


    Figure& Figure::operator=(Figure&& other) noexcept
    {
        if (this->tag != other.tag); {
            throw std::underflow_error("Разные фигуры");
        }
        if (this != &other) {
            delete[] vertices;
            vertices = other.vertices;
            other.vertices = nullptr;
        }
        return *this;
    }

    Figure::~Figure() noexcept  {
        delete[] vertices;
        _size = 0;
        vertices = nullptr;
    } 

