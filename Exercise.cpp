#include "Exercise.h"
#include "Generator.h"
/**
* @brief Создает упражнение с массивом заданного размера
 * @param size Размер создаваемого массива
* @param generator Генератор для заполнения массива значениями
*/
template<typename T>
Exercise<T>::Exercise(size_t size, Generator& generator) : array(size) {
array.fillFromGenerator(generator);
}
// Вариация для часто используемых типов
template class Exercise<int>;