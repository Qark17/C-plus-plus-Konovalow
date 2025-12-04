#include "Task2.h"
#include <cmath>
#include <vector>
    template<typename T>
    Task2<T>::Task2(const size_t size, const Generator& generator) : Exercise<T>(size, generator) {}
    template<typename T>
    bool Task2<T>::hasSameFirstTwoDigits(T number) const {
        number = std::abs(number);
        if (number < 10) return false;
        while (number >= 100) number /= 10;
        return (number / 10) == (number % 10);
    }
    template<typename T>
    Array<T> Task2<T>::execute() const {
        std::vector<T> temp;

        for (size_t i = 0; i < this->array.getSize(); ++i) {
            if (!hasSameFirstTwoDigits(this->array[i])) {
                temp.push_back(this->array[i]);
            }
        }
        Array<T> result(temp.size());
        for (size_t i = 0; i < temp.size(); ++i) {
            result[i] = temp[i];
        }
        return result;
    }
    template<typename T>
    std::string Task2<T>::getDescription() const {
        return "Удалить элементы с одинаковыми первой и второй цифрами";
    }
    template class Task2<int>;