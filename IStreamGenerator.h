#pragma once
#include "Generator.h"
#include <iostream>
/**
* @brief Генератор, который читает значения из входного потока
*/
class IStreamGenerator : public Generator
{
private:
    std::istream& in; // Ссылка на входной поток
public:
    /**
    * @brief Конструктор генератора входного потока
    * @param in Входной поток для чтения значений (по умолчанию std::cin)
    */
    IStreamGenerator(std::istream& in = std::cin);
    /**
    * @brief Читает следующее значение из входного потока
    * @return Прочитанное целое число
    */
    int generate() override;
};
