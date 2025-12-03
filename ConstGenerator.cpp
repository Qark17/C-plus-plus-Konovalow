#include "ConstGenerator.h"
/**
* @brief Создает генератор, возвращающий указанное посто¤нное значение
* @param value «начение, которое будет возвращатьс¤ при каждом вызове generate()
*/
ConstGenerator::ConstGenerator(int value) : value(value) {}
/**
* @brief Всегда возвращает одно и то же значение
* @return постоянное значение генератора
*/
int ConstGenerator::generate()
{
    return value;
}