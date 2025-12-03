#include "IStreamGenerator.h"

    /**
     * @brief Создает генератор, связанный с указанным входным потоком
     * @param in Поток ввода для чтения значений
     */
    IStreamGenerator::IStreamGenerator(std::istream& in) : in{ in }
    {
    }
    /**
     * @brief Читает одно целое число из связанного потока ввода
     * @return Введенное пользователем целое число
     */
    int IStreamGenerator::generate()
    {
        int value = 0;
        this->in >> value;
        return value;
    }
