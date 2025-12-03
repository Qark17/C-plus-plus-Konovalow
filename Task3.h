#pragma once
#include "Exercise.h"
/**
 * @brief Задание 3: Построение нового массива по правилу
 * @tparam T Тип элементов массива
 */
template<typename T>
class Task3 : public Exercise<T> {
public:
    /**
     * @brief Конструктор задания 3
     * @param size Размер массива
     * @param generator Генератор для заполнения массива
     */
    Task3(size_t size, Generator& generator);
    /**
     * @brief Выполнить задание: построить новый массив по правилу
     * @return Новый массив с результатом
     */
    Array<T> execute() const override;
    /**
     * @brief Получить описание задания
     * @return Строка с описанием
     */
    std::string getDescription() const override;
};
