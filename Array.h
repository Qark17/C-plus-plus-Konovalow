#pragma once
#include <memory>
#include <iostream>
#include "Generator.h"

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size;
public:
    Array(size_t size = 0) : size(size), data(std::make_unique<T[]>(size)) {
        for (size_t i = 0; i < size; ++i) data[i] = T{};
    }
    Array(const Array& other) : size(other.size), data(std::make_unique<T[]>(other.size)) {
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    Array(Array&& other) noexcept : size(other.size), data(std::move(other.data)) {
        other.size = 0;
    }
    ~Array() = default;
    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    T& operator[](size_t index) {
        return data[index];
    }
    const T& operator[](size_t index) const {
        return data[index];
    }
    void fillFromGenerator(Generator& generator) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<T>(generator.generate());
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size; ++i) {
            os << arr.data[i];
            if (i < arr.size - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};