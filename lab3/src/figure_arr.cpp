#include "../header/figure_arr.h"

figureArray::figureArray() : size(0), capacity(3) {
    figures = new Figure*[capacity];
}

figureArray::~figureArray() {
    //здесь мемори леак, если у нас пропадает ссылка на число раньше
    //и тут вылезают крутые указатели для 4 лабы
    delete[] figures;
    figures = nullptr;
}

int figureArray::getSize() const{
    return (*this).size;
}

void figureArray::pushBack(Figure* figure)  {
    if (size >= capacity) {
        capacity *= 2;
        Figure** new_data = static_cast<Figure**>(realloc(figures, (capacity) * sizeof(Figure*)));
        if (new_data != nullptr) {
            figures = new_data; 
            figures[size++] = figure; 
        } else {
            std::cerr << "Ошибка: Не удалось выделить память для push_back." << std::endl;
        }
    }
    figures[size++] = figure;
}

std::ostream& operator<<(std::ostream& out, const figureArray& _this) {
    for (size_t i = 0; i < _this.size; ++i) {
        std::cout << *(_this.figures[i]);
    }
    return out;
}

void figureArray::findAllCenters() {
    for (size_t i = 0; i < size; i++) {
        std::cout << figures[i]->findCenter() << ' ';
        //std::cout << "Центр фигуры под номером " << i + 1 << " находится в точке "<< figures[i]->findCenter() << '\n'; 
    }
}

void figureArray::findAllAreas() {
    for (size_t i = 0; i < size; i++) {
        std::cout << double(*figures[i]) << ' ';
        //std::cout << "Площадь фигуры под номером " << i + 1 << " равна " << double(*figures[i]) << '\n';
    }
}

double figureArray::findSumAreas() {
    double result = 0;
    for (size_t i = 0; i < size; i++) {
        result += double(*figures[i]);
    }
    return result;
}

void figureArray::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::underflow_error("Index out of range");
        return;
    }

    figures[index] = NULL;
    for (int i = index; i < size - 1; i++) {
        figures[i] = figures[i + 1];
    }
    size--;
}