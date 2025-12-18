#pragma once
#include <string>

/// @brief Класс для представления ингредиента
/// @details Содержит информацию об ингредиенте, его стоимости и поставщике
class Ingredient {
private:
    std::string name;
    std::string unit;
    double pricePerUnit;
    std::string supplierName;
    int minOrderQuantity;
    int stockQuantity;

public:
    /// @brief Конструктор ингредиента
    Ingredient(const std::string& name, const std::string& unit,
        double price, const std::string& supplier,
        const int minOrder = 1, const int stock = 0);

    std::string getName() const;
    std::string getUnit() const;
    double getPricePerUnit() const;
    std::string getSupplierName() const;
    int getMinOrderQuantity() const;
    int getStockQuantity() const;

    void setPricePerUnit(const double price);
    void setSupplierName(const std::string& supplier);
    void setStockQuantity(const int quantity);

    double calculateCost(const double amount) const;
    bool canOrder(const double amount) const;
    void updateStock(const int delta);
    bool isLowStock() const;
};