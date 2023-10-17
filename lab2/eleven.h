#pragma once 

#include <iostream>
#include <initializer_list>
#include <string>
#include <cstring> // Для функции memcpy

class Eleven {

private:
    size_t getSize();
    unsigned char getElement(int iter);
    void setElement(int iter, unsigned char value);
    void setValue(const std::string& value);
    void push_back(char digit);
    bool isValid(unsigned char a);

public:
    Eleven();
    Eleven(const size_t & n, unsigned char elem);
    Eleven(const std::initializer_list<unsigned char> & t);
    Eleven(const Eleven &other);
    Eleven(const std::string & t);
    Eleven(Eleven&& other) noexcept;

    virtual ~Eleven() noexcept;

    void removeLeadingZeros();
    void swap(Eleven& first, Eleven& second) noexcept;

    bool operator>(const Eleven & other) const;
    bool operator<(const Eleven & other) const;
    bool operator==(const Eleven & other) const;

    friend std::ostream & operator<<(std::ostream &stream, const Eleven & Eleven);
    friend std::istream & operator>>(std::istream & stream, Eleven & Eleven);
    
    Eleven& operator=(const Eleven & other);

    Eleven operator+(const Eleven & other) const;
    Eleven operator-(const Eleven & other) const;
    Eleven &operator+=(const Eleven & other);
    Eleven &operator-=(const Eleven & other);

private:
    size_t size;
    unsigned char* data;
};