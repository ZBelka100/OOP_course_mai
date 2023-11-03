#include "../header/figure_arr.h"
#include <memory>

//тут по логике не так должно быть
//или так, но я пока



//переделать тут все на shared_pointer
template <Number X, Number Y>
figureArray<X,Y>::figureArray() : size(0), capacity(3) {
    figures = new std::shared_ptr<Figure<X,Y>>[capacity];
}
template <Number X, Number Y>
figureArray<X,Y>::~figureArray() {
    //здесь мемори леак, если у нас пропадает ссылка на число раньше
    //и тут вылезают крутые указатели для 4 лабы
    delete[] figures;
    figures = nullptr;
}
template <Number X, Number Y>
int figureArray<X,Y>::getSize() const{
    return (*this).size;
}
template <Number X, Number Y>
void figureArray<X,Y>::pushBack(std::shared_ptr<Figure<X,Y>> figure)  {
    if (size >= capacity) {
        capacity *= 2;
        std::shared_ptr<Figure<X, Y>>* new_data = static_cast<std::shared_ptr<Figure<X,Y>>*>(realloc(figures, (capacity) * sizeof(std::shared_ptr<Figure<X,Y>>)));//тут
        if (new_data != nullptr) {
            figures = new_data; 
            figures[size++] = figure; 
        } else {
            std::cerr << "Ошибка: Не удалось выделить память для push_back." << std::endl;
        }
    }
    figures[size++] = figure;
}
template <Number X, Number Y>
std::ostream& operator<<(std::ostream& out, const figureArray<X,Y>& _this) {//тут странно будет работать
    for (size_t i = 0; i < _this.size; ++i) {
        std::cout << *(_this.figures[i]);
    }
    return out;
}
template <Number X, Number Y>
void figureArray<X,Y>::findAllCenters() {
    for (size_t i = 0; i < size; i++) {
        std::cout << figures[i]->findCenter() << ' ';
        //std::cout << "Центр фигуры под номером " << i + 1 << " находится в точке "<< figures[i]->findCenter() << '\n'; 
    }
}
template <Number X, Number Y>
void figureArray<X,Y>::findAllAreas() {
    for (size_t i = 0; i < size; i++) {
        std::cout << double(*figures[i]) << ' ';
        //std::cout << "Площадь фигуры под номером " << i + 1 << " равна " << double(*figures[i]) << '\n';
    }
}
template <Number X, Number Y>
double figureArray<X,Y>::findSumAreas() {
    double result = 0;
    for (size_t i = 0; i < size; i++) {
        result += double(*figures[i]);
    }
    return result;
}
template <Number X, Number Y>
void figureArray<X,Y>::remove(int index) {
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
