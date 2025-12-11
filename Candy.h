#pragma once
#include "ProductBase.h"
#include <string>

/// @brief Класс для представления конфет
/// @details Наследуется от ProductBase, добавляет свойства конфет
class Candy : public ProductBase {
private:
    std::string flavor;
    bool hasWrapper;
    bool isSugarFree;
    std::string texture;

public:
    /// @brief Конструктор конфет
    Candy(const std::string& name, const std::string& code,
        double price, int quantity, const std::string& flavor,
        bool wrapper, bool sugarFree = false,
        const std::string& texture = "твердая", double cost = 0.0);

    std::string getType() const override;
    std::string getDescription() const override;

    std::string getFlavor() const;
    bool hasWrapperCandy() const;
    bool isSugarFreeCandy() const;
    std::string getTexture() const;

    void setFlavor(const std::string& newFlavor);
};