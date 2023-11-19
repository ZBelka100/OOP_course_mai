#include <chrono>
#include <list>
#include <iostream>
#include "./src/allocator.h"
#include "./src/list.h"
#include "./src/iterator.h"
#include <map>

int factorial(int n) {
    return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}

int main() {
    std::map<int, int, std::less<int>,Allocator<std::pair<const int,int>>> my_map;
    for (int i = 0; i < 10; ++i) {
        my_map[i] = factorial(i);
    }
    my_map.erase(1);
    my_map.erase(1);

    for(const auto& [k,v]: my_map) {
        std::cout << k << "->" << v << std::endl;
    }

    List<int, Allocator<Node<int>>> myList;
    
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    Iterator<int> it = myList.begin();
    for (it; it != myList.end(); ++it) {
        std::cout << *it << ' ';
    }
    return 0;
}