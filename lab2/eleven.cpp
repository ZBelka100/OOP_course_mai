#include "eleven.h"


    // Конструктор по умолчанию +
    Eleven::Eleven() : data(nullptr), size(0){}


   // Конструктор с размером и начинкой +
    Eleven::Eleven(const size_t& n, unsigned char elem = '0') : size(n) {
    data = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        if ((elem >= '0' && elem <= '9') || (elem == 'A')) {
            data[i] = elem;
        } else {
            delete[] data;
            throw std::invalid_argument("Некорректный символ в числе");
        }
    }
}


    // Конструктор с использованием списка инициализации +
    Eleven::Eleven(const std::initializer_list<unsigned char>& t) : size(t.size()) {
        data = new unsigned char[size];
        size_t i = t.size() - 1;
        for (const auto& elem : t) {
            if ((elem >= '0' && elem <= '9') || (elem == 'A')) {
                data[i] = elem;
            } else {
                delete[] data; // Освободите ресурсы, если символ некорректный
                throw std::invalid_argument("Некорректный символ в числе");
            }
            --i;
        }
}


    // Конструктор, принимающий строку +
    Eleven::Eleven(const std::string& t) : size(t.size()) {
        data = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            char currentChar = t[i];
            if ((currentChar >= '0' && currentChar <= '9') || (currentChar == 'A')) {
                data[size - i - 1] = static_cast<unsigned char>(currentChar);
            } else {
                delete[] data; // Освободите ресурсы, если символ некорректный
                throw std::invalid_argument("Некорректный символ в числе");
            }
        }
    }


    // Конструктор копирования +
    Eleven::Eleven(const Eleven& other) : size(other.size) {
        data = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Конструктор перемещения +
    Eleven::Eleven(Eleven&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    // Деструктор +
    Eleven::~Eleven() noexcept {
        delete[] data;
    }

    //swap +
    void Eleven::swap(Eleven& first, Eleven& second) noexcept {
        std::swap(first.data, second.data);
        std::swap(first.size, second.size);
    }

    void Eleven::push_back(char digit) {
        unsigned char* new_data = static_cast<unsigned char*>(realloc(data, (size + 1) * sizeof(unsigned char)));//быть может увеличивать в два раза?
        if (new_data != nullptr) {
            data = new_data;  // Обновляем указатель на новый выделенный блок памяти
            data[size] = digit;  // Добавляем новый символ в конец массива
            ++size;  // Увеличиваем размер
        } else {
            std::cerr << "Ошибка: Не удалось выделить память для push_back." << std::endl;
        }
    }

    void Eleven::removeLeadingZeros() {
        if (size <= 1) {
            // Если размер числа меньше или равен 1, нет ведущих нулей
            return;
        }
        bool leading_zero = true; // Флаг, указывающий, что мы видим ведущие нули
        int zerosCounter = 0;
        for (int i = size - 1; i > -1; --i) {
            if (data[i] != '0' || !leading_zero) {
                leading_zero = false; // Отключаем флаг ведущих нулей
            } else {
                ++zerosCounter;
            }
        }
        size -= zerosCounter;
        if (zerosCounter && size) {
            unsigned char* new_data = static_cast<unsigned char*>(realloc(data, size*sizeof(unsigned char)));
            data = new_data;
        } 
        if (!size) {
            size = 1;
            unsigned char* new_data = new unsigned char[1];
            new_data[0] = '0';
        }
        return;
    } 


    


    // Перегрузка оператора вывода для удобства вывода массива +
    std::ostream& operator<<(std::ostream& out, const Eleven& arr) {
        for (int i = arr.size - 1; i > -1; --i) {
            out << arr.data[i];
        }
        return out;
    }  

    bool Eleven::operator>(const Eleven &other) const {
        if (size > other.size) {
            return true;
        } else if (size == other.size) {
            for (int i = size - 1; i >= 0; i--) {
                if (data[i] > other.data[i]) {
                    return true;
                } else if (data[i] < other.data[i]) {
                    return false;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    bool Eleven::operator<(const Eleven &other) const {
        if (size < other.size) {
            return true;
        } else if (size == other.size) {
            for (int i = size - 1; i >= 0; i--) {
                if (data[i] < other.data[i]) {
                    return true;
                } else if (data[i] > other.data[i]) {
                    return false;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    bool Eleven::operator==(const Eleven& second) const {
        if (size == second.size) {
            for (int i = 0; i < size; ++i) {
                if (data[i] != second.data[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    Eleven& Eleven::operator=(const Eleven & other) {
        size = other.size;
        delete[] data;
        data = new unsigned char[size];
        std::memcpy(data, other.data, size * sizeof(unsigned char));
        return *this;
    }

    //сложение +
    Eleven Eleven::operator+(const Eleven& second) const {
        Eleven first = *this;
        Eleven result(std::max(first.size, second.size));
        size_t carry = 0;
        for (size_t i = 0; i < result.size || carry; ++i) {
            if (i == result.size) {
                result.push_back('1');
                break;
            }
            int sum = carry;
            if (i < first.size) {
                if (first.data[i] == 'A') {
                    sum += 10;
                } else {
                    sum += first.data[i] - '0';
                }
            }
            if (i < second.size) {
                if (second.data[i] == 'A') {
                    sum += 10;
                } else {
                    sum += second.data[i] - '0';
                }
            }
            if (sum%11 == 10) {
                result.data[i] = 'A';
            } else {
                result.data[i] = sum%11 + '0';
            }
            carry = sum / 11;
        }
        return result;
        
    }

    Eleven Eleven::operator-(const Eleven& second) const {
         Eleven first = *this;
        size_t carry = 0;
        if (first<second) {
            throw std::invalid_argument("Попытка вычитания большего числа из меньшего");
        }
        Eleven result(first.size);
        for (size_t i = 0; i < result.size; ++i) {
            int firstDigit = 0 - carry;
            carry = 0;
            int secondDigit = 0;
            if (first.data[i] == 'A') {
                firstDigit += 10;
            } else {
                firstDigit += first.data[i] - '0';
            }
            if (i < second.size) {
                if (second.data[i] == 'A') {
                    secondDigit += 10;
                } else {
                    secondDigit += second.data[i] - '0';
                }
            } else {
                secondDigit = 0;
            }
            if (firstDigit < secondDigit) {
                // Занимаем у старших разрядов
                firstDigit += 11;
                carry = 1;
            }
            result.data[i] = ((firstDigit - secondDigit) + '0' == ':') ? 'A' : (firstDigit - secondDigit) + '0';
        }
        result.removeLeadingZeros();
        return result;
        
    }
    Eleven &Eleven::operator+=(const Eleven & other) {
        *(this)  = *(this) + other;
        return *(this);
    }
    
    Eleven &Eleven::operator-=(const Eleven & other) {
        *(this) = *(this) - other;
        return *(this);
    }
