#include <iostream>
#include <initializer_list>
#include <string>
#include "eleven.h"


int main() {
    //А что тут писать
    Eleven s1{'A', '3', '4'};
    Eleven s2{'A', '8', '2', '9', '1', '0'};
    std::cout << "a: " << s1 << '\n';
    std::cout << "b: " << s2 << '\n';
    std::cout << "a - b: " << s2 - s1 << '\n';
    return 0;
}
