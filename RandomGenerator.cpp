#include "RandomGenerator.h"
/**
* @brief Создает генератор случайных чисел для указанного диапазона
* @param min Нижняя граница диапазона
* @param max Верхняя граница диапазона
*/
RandomGenerator::RandomGenerator(const int min, const int max)
{
    this->generator = std::mt19937(std::random_device{}());
    this->distribution = std::uniform_int_distribution<int>(min, max);
}
/**
* @brief Генерирует очередное случайное число
* @details Каждый вызов возвращает новое случайное число
* в диапазоне [min, max], заданном при создании генератора
* @return Случайное целое число в установленном диапазоне
*/
int RandomGenerator::generate()
{
return this->distribution(this->generator);
}
