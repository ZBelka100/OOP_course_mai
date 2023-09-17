#include <iostream>
#include <string>
#include "extractnumber.h"

int main() {
    std::string s;
    std::cin >> s;
    std::cout << extractnumber(s) << '\n';
}
