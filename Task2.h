#pragma once
#include "Exercise.h"
#include <vector>
/**
 * @brief Задание 2: Удаление элементов с одинаковыми первыми двумя цифрами
 * @tparam T Тип элементов массива
 */
template<typename T>
class Task2 : public Exercise<T> {
public:
    /**
    * @brief Конструктор задания 2
    * @param size Размер массива
    * @param generator Генератор для заполнения массива
    */
    Task2(const size_t size, const Generator& generator);
    /**
    * @brief Выполнить задание: удалить элементы с одинаковыми первой и второй цифрами
    * @return Новый массив с результатом
    */
    Array<T> execute() const override;
    /**
     * @brief Получить описание задания
     * @return Строка с описанием
     */
    std::string getDescription() const override;
private:
    /**
     * @brief Проверить, имеют ли число одинаковые первые две цифры
     * @param number Число для проверки
     * @return true если первые две цифры одинаковы, иначе false
     */
    bool hasSameFirstTwoDigits(const T number) const;
};
