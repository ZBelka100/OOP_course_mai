#pragma once

#include <iostream>
#include <concepts>
#include <memory>

template <typename T>
class DynamicArray {
private:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t capacity;

public:
    DynamicArray();
    DynamicArray(size_t initialSize);
    ~DynamicArray();

    T* begin();
    T* end();

    DynamicArray(DynamicArray &other);
    DynamicArray(DynamicArray &&other) noexcept;

    T& operator[](size_t index);
    size_t getSize() const;
    void pushBack(T& element);
    void remove(int index);

    template <typename _T>
    friend std::ostream& operator<<(std::ostream& out, const DynamicArray<_T> arr);
};
template <typename T>
double findSumAreas(DynamicArray<T> &arr);
template <typename T>
void findAllCenters(DynamicArray<T> &arr);
template <typename T>
void findAllAreas(DynamicArray<T> &arr);

#include </home/andrey/Desktop/cpp_memes/oop/OOP_course_mai/test_lab4/lab4/header/array.hpp>//почему просто array не работает? А хер его знает