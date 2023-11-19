#include <iostream>

#include "./allocator.h"
#include "./node.h"
#include "./iterator.h"

template <typename T, class Allocator>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    Allocator allocator;

public:
    List();
    ~List();

    Iterator<T> begin() const;
    Iterator<T> end() const;
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;

    void push_front(const T& value);
    void push_back(const T& value); 
    void pop_back();
    void pop_front();
    T& front();
    T& back();
    bool empty() const;
    void clear();
};

template <typename T, class Allocator>
List<T, Allocator>::List() : head(nullptr), tail(nullptr), allocator() {}

template <typename T, class Allocator> 
List<T, Allocator>::~List() {
    clear();
}

template <typename T, class Allocator>
Iterator<T> List<T, Allocator>::begin() const {
    Iterator<T> begin(head);
    return begin;
}

template <typename T, class Allocator>
Iterator<T> List<T, Allocator>::end() const {
    Iterator<T> end(tail);
    end++;
    return end;
}

template <typename T, class Allocator>
ConstIterator<T> List<T, Allocator>::cbegin() const {
    ConstIterator<T> begin(head);
    return begin;
}

template <typename T, class Allocator>
ConstIterator<T> List<T, Allocator>::cend() const {
    ConstIterator<T> end(tail);
    end++;
    return end;
}


template <typename T, class Allocator> 
void List<T, Allocator>::push_front(const T& value) {
    Node<T>* newNode = allocator.allocate(1);
    newNode->next = nullptr;
    newNode->prev = nullptr;
    allocator.construct(newNode, value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template <typename T, class Allocator> 
void List<T, Allocator>::push_back(const T& value) {
    Node<T>* newNode = allocator.allocate(1);
    newNode->next = nullptr;
    newNode->prev = nullptr;
    allocator.construct(newNode, value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

template <typename T, class Allocator> 
void List<T, Allocator>::pop_back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }

    if (head == tail) {
        allocator.destroy(head);
        allocator.deallocate(head, 1);
        head = tail = nullptr;
    } else {
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        allocator.destroy(temp);
        allocator.deallocate(temp, 1);
    }
}

template <typename T, class Allocator> 
void List<T, Allocator>::pop_front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }

    if (head == tail) {
        allocator.destroy(head);
        allocator.deallocate(head, 1);
        head = tail = nullptr;
    } else {
        Node<T>* temp = head;
        head = head->next;
        head->prev = nullptr;
        allocator.destroy(temp);
        allocator.deallocate(temp, 1);
    }
}


template <typename T, class Allocator>
T& List<T, Allocator>::front() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return head->data;
}

template <typename T, class Allocator>
T& List<T, Allocator>::back() {
    if (empty()) {
        throw std::out_of_range("List is empty");
    }
    return tail->data;
}

template <typename T, class Allocator>
bool List<T, Allocator>::empty() const {
    return head == nullptr;
}

template <typename T, class Allocator>
void List<T, Allocator>::clear() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        allocator.destroy(temp);
        allocator.deallocate(temp, 1);
    }
    tail = nullptr;
}
