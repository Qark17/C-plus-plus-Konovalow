#include "Task1.h"
#include <cmath>
    template<typename T>
    Task1<T>::Task1(size_t size, Generator& generator) : Exercise<T>(size, generator) {}

    template<typename T>
    Array<T> Task1<T>::execute() const {
        Array<T> result = this->array;

        // Найти последний отрицательный элемент
        int lastNegativeIndex = -1;
        for (size_t i = 0; i < result.getSize(); ++i) {
            if (result[i] < 0) {
                lastNegativeIndex = i;
            }
        }

        // Заменить на модуль первого элемента
        if (lastNegativeIndex != -1) {
            result[lastNegativeIndex] = std::abs(result[0]);
        }

        return result;
    }

    template<typename T>
    std::string Task1<T>::getDescription() const {
        return "Заменить последний отрицательный элемент на модуль первого элемента";
    }

    template class Task1<int>;
