#pragma once
#include "Array.h"
#include <memory>
#include <string>
/**
 * @brief Базовый класс для различных операций с массивами
 * @tparam T Тип элементов массива
 */
template<typename T>
class Exercise {
protected:
    Array<T> array;
public:
    /**
     * @brief Конструктор упражнения
     * @param size Размер массива
     * @param generator Генератор для заполнения массива
     */
    Exercise(const size_t size, const Generator& generator);
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Exercise() = default;
    /**
      * @brief Получить константную ссылку на массив
      * @return Константная ссылка на объект Array
      */
    const Array<T>& getArray() const { return array; }
    /**
     * @brief Выполнить операцию над массивом
     * @return Новый массив с результатом операции
     */
    virtual Array<T> execute() const = 0;
    /**
     * @brief Получить описание операции
     * @return Строка с описанием операции
     */
    virtual std::string getDescription() const = 0;

};
