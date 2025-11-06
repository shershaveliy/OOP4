#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>
#include <cstddef>

template<class T>
class Array {
private:
    std::unique_ptr<T[]> data_;  // Умный указатель на динамический массив T
    std::size_t size_;           // Текущее количество элементов
    std::size_t capacity_;       // Вместимость массива (сколько элементов можно хранить)

    // Увеличение вместимости массива
    void resize(std::size_t new_capacity){
        // Выделяем новый массив через make_unique
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

        // Перемещаем старые элементы в новый массив
        for (std::size_t i = 0; i < size_; ++i){
            new_data[i] = std::move(data_[i]);
        }
        // Меняем владение — старый массив автоматически уничтожится
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    // Конструктор по умолчанию
    Array() : data_(nullptr), size_(0), capacity_(0) {}

    // Конструктор с начальной вместимостью
    explicit Array(std::size_t initial_capacity)
        : data_(nullptr), size_(0), capacity_(0){
        if (initial_capacity > 0){
            data_ = std::make_unique<T[]>(initial_capacity);
            capacity_ = initial_capacity;
        }
    }

    // Конструктор копирования
    Array(const Array& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_){
        if (capacity_ > 0) {
            data_ = std::make_unique<T[]>(capacity_);
            for (std::size_t i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        }
    }

    // Оператор присваивания копированием
    Array& operator=(const Array& other){
        if (this != &other){
            data_.reset(); // Освобождаем старый массив
            size_ = other.size_;
            capacity_ = other.capacity_;
            if (capacity_ > 0) {
                data_ = std::make_unique<T[]>(capacity_);
                for (std::size_t i = 0; i < size_; ++i)
                    data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // Конструктор перемещения
    Array(Array&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_){
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Оператор присваивания перемещением
    Array& operator=(Array&& other) noexcept{
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Добавление элемента в конец массива (копирование)
    void push_back(const T& value){
        if (size_ >= capacity_)
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }

    // Добавление элемента в конец массива (перемещение)
    void push_back(T&& value){
        if (size_ >= capacity_)
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    // Удаление элемента по индексу
    void erase(std::size_t index){
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        for (std::size_t i = index; i + 1 < size_; ++i)
            data_[i] = std::move(data_[i + 1]);
        --size_;
    }
    //Доступ к элементу
    T& operator[](std::size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }
    const T& operator[](std::size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
};

#endif
