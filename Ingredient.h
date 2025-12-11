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
        int minOrder = 1, int stock = 0);

    std::string getName() const;
    std::string getUnit() const;
    double getPricePerUnit() const;
    std::string getSupplierName() const;
    int getMinOrderQuantity() const;
    int getStockQuantity() const;

    void setPricePerUnit(double price);
    void setSupplierName(const std::string& supplier);
    void setStockQuantity(int quantity);

    double calculateCost(double amount) const;
    bool canOrder(double amount) const;
    void updateStock(int delta);
    bool isLowStock() const;
};