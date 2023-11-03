#include "../header/point.h"
#include "../header/figure.h"

template <Number X, Number Y>     
    Figure<X,Y>::Figure() : vertices(nullptr), _size(0) {};
template <Number X, Number Y>    
    Figure<X,Y>::Figure(int n) {
        _size = n;
        vertices = new point<X,Y>[n];//?????
    };
template <Number X, Number Y>    
    point<X,Y> Figure<X,Y>::findCenter() const {//тут видимо насильственно нужно привести в дабл
        point center = {0.0, 0.0};
        for (int i = 0; i < _size; ++i) {
            center.x += vertices[i].x;
            center.y += vertices[i].y;
        }
        center.x /= _size;
        center.y /= _size;
        return center;
    }
template <Number X, Number Y>    
    bool Figure<X,Y>::isThisFigure() {
        return true;
    }
template <Number X, Number Y>    
    std::string Figure<X,Y>::draw() const {
        return "This is a generic figure.";
    }
template <Number X, Number Y>    
    Figure<X,Y>::operator double() const{
        return (vertices[0].x * (vertices[1].y - vertices[2].y) + vertices[1].x * (vertices[2].y - vertices[0].y) + vertices[2].x * (vertices[0].y - vertices[1].y))/2;
    }
template <Number X, Number Y>    
    std::istream& operator>>(std::istream& in, Figure<X,Y>& figure) {
        for (int i = 0; i < figure._size; ++i) {
            in >> figure.vertices[i].x >> figure.vertices[i].y;
        }
        if (figure.isThisFigure()) {
            return in;
        }
        throw std::invalid_argument("Ты что то перепутал");
    }
template <Number X, Number Y>    
    std::ostream& operator<<(std::ostream& out, const Figure<X,Y>& figure) {
        for (int i = 0; i < figure._size; ++i) {
            out << "(" << figure.vertices[i].x << ", " << figure.vertices[i].y << ") \n";
        }
        return out;
    } 
template <Number X, Number Y>    
    bool Figure<X,Y>::operator==(const Figure& other) const {
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
template <Number X, Number Y>    
    Figure<X,Y>& Figure<X,Y>::operator=(Figure<X,Y>& other) {
        if (_size != other._size) {
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

template <Number X, Number Y>    
    Figure<X,Y>& Figure<X,Y>::operator=(Figure<X,Y>&& other) noexcept
    {
        if (this->_size != other._size); {
            throw std::underflow_error("Разные фигуры");
        }
        if (this != &other) {
            delete[] vertices;
            vertices = other.vertices;
            other.vertices = nullptr;
        }
        return *this;
    }
template <Number X, Number Y>    
    Figure<X,Y>::~Figure() noexcept  {
        delete[] vertices;
        _size = 0;
        vertices = nullptr;
    } 

