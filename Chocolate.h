#pragma once
#include "ProductBase.h"// ингридиент
#include <string>
/// @brief Класс для представления шоколадных изделий
/// @details Наследуется от ProductBase, добавляет специфичные свойства шоколада
class Chocolate : public ProductBase {
private:
    int cocoaPercentage;
    bool isDark;
    std::string filling;
public:
    /// @brief Конструктор шоколада
    Chocolate(const std::string& name, const std::string& code,
        double price, int quantity, int cocoaPercent,
        bool dark, const std::string& filling = "", double cost = 0.0);
    std::string getType() const override;
    std::string getDescription() const override;
    int getCocoaPercentage() const;
    bool isDarkChocolate() const;
    std::string getFilling() const;
    void setFilling(const std::string& newFilling);
    bool isBitter() const;
};