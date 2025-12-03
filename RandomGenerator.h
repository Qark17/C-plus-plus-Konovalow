#pragma once
#include "Generator.h"
#include <random>
/**
 * @brief Генератор, создающий случайные числа в указанном диапазоне
 */
class RandomGenerator : public Generator
{
private:
    std::uniform_int_distribution<int> distribution; ///< Распределение чисел в диапазоне
    std::mt19937 generator; ///< Генератор случайных чисел
public:
    /**
     * @brief Конструктор генератора случайных чисел
     * @param min Минимальное значение диапазона
     * @param max Максимальное значение диапазона
     */
    RandomGenerator(int min, int max);
    /**
     * @brief Генерирует случайное число в заданном диапазоне
     * @return Случайное целое число от min до max включительно
     */
    int generate() override;
};
