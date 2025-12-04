#include "Task3.h"
    template<typename T>
    Task3<T>::Task3(const size_t size, const Generator& generator) : Exercise<T>(size, generator) {}
    template<typename T>
    Array<T> Task3<T>::execute() const {
        Array<T> result(this->array.getSize());

        for (size_t i = 0; i < result.getSize(); ++i) {
            if (this->array[i] % 2 == 0) {
                result[i] = static_cast<T>(i) * this->array[i];
            }
            else {
                result[i] = -this->array[i];
            }
        }
        return result;
    }
    template<typename T>
    std::string Task3<T>::getDescription() const {
        return "Построить новый массив: четные * индекс, нечетные -> отрицательные";
    }
    template class Task3<int>;