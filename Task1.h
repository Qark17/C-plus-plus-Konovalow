#pragma once
#include "Exercise.h"
/**
 * @brief Задание 1: Замена последнего отрицательного элемента
 * @tparam T Тип элементов массива
 */
template<typename T>
class Task1 : public Exercise<T> {
public:
    /**
     * @brief Конструктор задания 1
     * @param size Размер массива
     * @param generator Генератор для заполнения массива
     */
    Task1(const size_t size, const Generator& generator);
    /**
     * @brief Выполнить задание: заменить последний отрицательный элемент на модуль первого
     * @return Новый массив с результатом
     */
    Array<T> execute() const override;
    /**
     * @brief Получить описание задания
     * @return Строка с описанием
     */
    std::string getDescription() const override;
};
