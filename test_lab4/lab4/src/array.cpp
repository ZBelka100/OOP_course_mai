template <typename T>
class DynamicArray {
private:
    T data[];
    size_t size; 
    size_t capacity;

public:
    DynamicArray(size_t initialCapacity = 2) : size(0), capacity(initialCapacity) {
        data = new T[initialCapacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    void pushBack(const T& element) {
        if (size >= capacity) {
            capacity *= 2;
            T[] new_data = static_cast<T[]>(realloc(data, (capacity) * sizeof(T)));
            if (new_data != nullptr) {
                data = new_data; 
                figures[size++] = figure; 
            } else {
                std::cerr << "Ошибка: Не удалось выделить память для push_back." << std::endl;
            }
        }
        figures[size++] = figure;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::underflow_error("Index out of range");
            return;
        }

        figures[index] = NULL;
        for (int i = index; i < size - 1; i++) {
            figures[i] = figures[i + 1];
        }
        size--;
    }

};

