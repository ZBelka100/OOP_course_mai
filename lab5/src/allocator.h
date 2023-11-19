#pragma once

#include <iostream>
#include <deque>

template <class T>
class Allocator {
private:
    std::deque<T*> _used_blocks;
    std::deque<T**> _free_blocks;

public:
    static constexpr size_t max_count = 100000;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;

    Allocator();

    ~Allocator();

    template <class U>
    struct rebind {
        using other = Allocator<U>;
    };

    T* allocate(size_t n);

    void deallocate(T *pointer, size_t);

    template <typename... Args>
    void construct(pointer p, Args &&...args);

    void destroy(pointer p);
    //void erase(T* element);
};

template <class T, class U>
constexpr bool operator==(const Allocator<T> &lhs, const Allocator<U> &rhs);

template <typename T, typename U, size_t BLOCK_COUNT>
constexpr bool operator!=(const Allocator<T> &lhs, const Allocator<U> &rhs);

template <class T>
Allocator<T>::Allocator() {
    for (size_t i = 0; i < max_count; ++i) {
        T* block = new T;
        _used_blocks.push_back(block);
        _free_blocks.push_back(&_used_blocks.back());
    }
}

template <class T>
Allocator<T>::~Allocator() {
    for (T* block : _used_blocks) {
        delete block;
    }
    while (!_free_blocks.empty()) {
        T** blockPtr = _free_blocks.front();
        _free_blocks.pop_front();
        // T* block = *blockPtr;
        // delete block;
    }
    _free_blocks.clear();
    _used_blocks.clear();
}

template <class T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_t n) {
    T* result = nullptr;
    if (!_free_blocks.empty() && n) {
        result = *_free_blocks.back();
        _free_blocks.pop_back();
    } else {
        std::cout << "allocator: No memory exception :-)" << std::endl;
    }
    return result;
}

template <class T>
void Allocator<T>::deallocate(T *pointer, size_t) {
    _free_blocks.push_back(&pointer);
}

template <class T>
template <typename... Args>
void Allocator<T>::construct(pointer p, Args &&...args) {
    new (p) T(std::forward<Args>(args)...);
}

template <class T>
void Allocator<T>::destroy(Allocator<T>::pointer p) {
    p->~T();
}

template <class T, class U>
constexpr bool operator==(const Allocator<T> &lhs, const Allocator<U> &rhs) {
    return true;
}

template <typename T, typename U, size_t BLOCK_COUNT>
constexpr bool operator!=(const Allocator<T> &lhs, const Allocator<U> &rhs) {
    return false;
}
/*
template <class T>
void Allocator<T>::erase(T* element) {
    // Find the iterator pointing to the element in used_blocks
    auto it = std::find(_used_blocks.begin(), _used_blocks.end(), element);

    if (it != _used_blocks.end()) {
        // Erase the element from used_blocks
        _used_blocks.erase(it);

        // Push the pointer to the erased element into free_blocks
        _free_blocks.push_back(&element);
    } else {
        std::cout << "allocator: Element not found for erase operation." << std::endl;
    }
}*/