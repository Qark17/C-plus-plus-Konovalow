#include "Ingredient.h"

Ingredient::Ingredient(const std::string& name, const std::string& unit,
    double price, const std::string& supplier,
    int minOrder, int stock)
    : name(name), unit(unit), pricePerUnit(price),
    supplierName(supplier), minOrderQuantity(minOrder),
    stockQuantity(stock)
{
    if (pricePerUnit < 0) pricePerUnit = 0;
    if (minOrderQuantity < 1) minOrderQuantity = 1;
    if (stockQuantity < 0) stockQuantity = 0;
}

std::string Ingredient::getName() const { return name; }
std::string Ingredient::getUnit() const { return unit; }
double Ingredient::getPricePerUnit() const { return pricePerUnit; }
std::string Ingredient::getSupplierName() const { return supplierName; }
int Ingredient::getMinOrderQuantity() const { return minOrderQuantity; }
int Ingredient::getStockQuantity() const { return stockQuantity; }

void Ingredient::setPricePerUnit(double price) {
    if (price >= 0) pricePerUnit = price;
}

void Ingredient::setSupplierName(const std::string& supplier) {
    supplierName = supplier;
}

void Ingredient::setStockQuantity(int quantity) {
    if (quantity >= 0) stockQuantity = quantity;
}

double Ingredient::calculateCost(double amount) const {
    if (amount <= 0) return 0.0;
    return pricePerUnit * amount;
}

bool Ingredient::canOrder(double amount) const {
    return amount >= minOrderQuantity;
}

void Ingredient::updateStock(int delta) {
    stockQuantity += delta;
    if (stockQuantity < 0) stockQuantity = 0;
}

bool Ingredient::isLowStock() const {
    return stockQuantity < minOrderQuantity;
}