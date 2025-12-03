#pragma once
#include <memory>
#include <iostream>
#include "Generator.h"
/**
 * @brief Шаблонный класс для работы с динамическим массивом
 * @tparam T Тип элементов массива
 */
template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size;
public:
    /**
     * @brief Конструктор массива
     * @param size Размер создаваемого массива (по умолчанию 0)
     */
    Array(size_t size = 0) : size(size), data(std::make_unique<T[]>(size)) {
        for (size_t i = 0; i < size; ++i) data[i] = T{};
    }
    /**
     * @brief Конструктор копирования
     * @param other Массив для копирования
     */
    Array(const Array& other) : size(other.size), data(std::make_unique<T[]>(other.size)) {
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    Array(Array&& other) noexcept : size(other.size), data(std::move(other.data)) {
        other.size = 0;
    }
    /**
     * @brief Деструктор
     */
    ~Array() = default;
    /**
     * @brief Получить размер массива
     * @return Текущий размер массива
     */
    size_t getSize() const { return size; }
    /**
     * @brief Проверить, пуст ли массив
     * @return true если массив пуст, иначе false
     */
    bool isEmpty() const { return size == 0;
    /**
     * @brief Оператор доступа к элементу по индексу (неконстантный)
     * @param index Индекс элемента
     * @return Ссылка на элемент массива
     */
    }
    T& operator[](size_t index) {
        return data[index];
    }
    /**
     * @brief Оператор доступа к элементу по индексу (константный)
     * @param index Индекс элемента
     * @return Константная ссылка на элемент массива
     */
    const T& operator[](size_t index) const {
        return data[index];
    }
    /**
     * @brief Заполнить массив значениями с помощью генератора
     * @param generator Генератор значений
     */
    void fillFromGenerator(Generator& generator) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<T>(generator.generate());
        }
    }
    /**
     * @brief Оператор вывода массива в поток
     * @param os Выходной поток
     * @param arr Массив для вывода
     * @return Ссылка на выходной поток
     */
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