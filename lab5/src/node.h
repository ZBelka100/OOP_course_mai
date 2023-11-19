#pragma once

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node();
    Node(const T& value);
    ~Node();

    const T& getValue() const;
    void setValue(const T& val);
    Node<T>* getNext() const;
    Node<T>* getPrev() const;
    void setNext(Node* ptr);
    void setPrev(Node* ptr);
};


template <typename T>
Node<T>::Node() : data(0), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::~Node() = default;

template <typename T>
const T& Node<T>::getValue() const {
    return data;
}

template <typename T>
void Node<T>::setValue(const T& val) {
    data = val;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template <typename T>
Node<T>* Node<T>::getPrev() const {
    return prev;
}
