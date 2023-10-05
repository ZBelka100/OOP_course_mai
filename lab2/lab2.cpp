#include <iostream>
#include <initializer_list>
#include <string>
#include "eleven.h"

//поправить вычитание


int main() {
    //А что тут писать
    Eleven s1{'A', '3', '4'};
    Eleven s2{'A', '8', '2', '9', '1', '0'};
    std::cout << "a: " << s1 << '\n';
    std::cout << "b: " << s2 << '\n';
    std::cout << "a - b: " << s1 - s2 << '\n';
    /*Eleven a;
    Eleven b(5, 'A'); // Создание массива из 5 элементов, каждый равен 10
    Eleven c = {'1', '2', '3'}; // Создание массива с использованием списка инициализации
    Eleven d("10A"); // Создание массива из строки
    Eleven e{b};
    std::cout << "a: " << a << '\n';//тут должен быть ноль, или не ноль
    std::cout << "b: " << b << '\n';
    std::cout << "c: " << c << '\n';
    std::cout << "d: " << d << '\n';
    std::cout << "e: " << e << '\n';
    Eleven f(std::move(d));
    std::cout << "d: " << d << '\n';
    std::cout << "f: " << f << '\n';
    std::cout << "sum: " << b + f << '\n';*/
    return 0;
}
