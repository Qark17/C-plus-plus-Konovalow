#pragma once
#include "Generator.h"
    /**
     * @brief Генератор, возвращающий одно и то же значение
     */
    class ConstGenerator : public Generator
    {
    private:
        int value; // const, возвращаемая генератором
    public:
        /**
         * @brief  конструктор генератора посто¤нных значений
         * @param value - Значение, которое будет возвращаться при каждом вызове
         */
        ConstGenerator(int value);
        /**
         * @brief Всегда возвращает одно и то же значение
         * @return Заданное при создании постоянное значение
         */
        int generate() override;
    };