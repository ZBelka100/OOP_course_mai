#pragma once

#include "./node.h"

template <typename T>
class ConstIterator {
private:
    Node<T>* current;
public:
    ConstIterator();
    explicit ConstIterator(Node<T>* node);

    ConstIterator& operator++();
    ConstIterator operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;
    T getData() const;
};

template <typename T>
class Iterator {
private:
    Node<T>* current;

public:
    Iterator();
    explicit Iterator(Node<T>* node);

    Iterator& operator++();
    Iterator operator++(int);

    T& operator*() const;
    T* operator->() const;

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    T getData() const;
};

template <typename T>
Iterator<T>::Iterator()
    : current(nullptr) {}

template <typename T>
Iterator<T>::Iterator(Node<T>* it)
    : current(it) {}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int) {
    Iterator tmp(*this);
    current = current->next;
    return tmp;
}

template <typename T>
T& Iterator<T>::operator*() const {
    if (!current) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return (current)->data;
}

template <typename T>
T* Iterator<T>::operator->() const {
    return &((current)->data);
}

template <typename T>
bool Iterator<T>::operator==(const Iterator& other) const {
    return current == other.current;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// ConstIterator

template <typename T>
ConstIterator<T>::ConstIterator()
    : current(nullptr) {}

template <typename T>
ConstIterator<T>::ConstIterator(Node<T>* it)
    : current(it) {}

template <typename T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    current = current->next;
    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    ConstIterator tmp(*this);
    current = current->next;
    return tmp;
}

template <typename T>
const T& ConstIterator<T>::operator*() const {
    if (!current) {
        throw std::out_of_range("Dereferencing end iterator");
    }
    return (current)->data;
}

template <typename T>
const T* ConstIterator<T>::operator->() const {
    return &((*current)->data);
}

template <typename T>
bool ConstIterator<T>::operator==(const ConstIterator& other) const {
    return current == other.current;
}

template <typename T>
bool ConstIterator<T>::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}