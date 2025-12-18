#include "ProductBase.h"

ProductBase::ProductBase(const std::string& name, const std::string& code,
    double price, int quantity, double cost)
    : name(name), productCode(code), price(price),
    quantity(quantity), productionCost(cost) {
}

std::string ProductBase::getDescription() const {
    return "Product: " + name + " (Code: " + productCode +
        "), Price: " + std::to_string(price) +
        ", Quantity: " + std::to_string(quantity);
}

std::string ProductBase::getName() const { return name; }
std::string ProductBase::getProductCode() const { return productCode; }
double ProductBase::getPrice() const { return price; }
int ProductBase::getQuantity() const { return quantity; }
double ProductBase::getProductionCost() const { return productionCost; }

double ProductBase::getProfitMargin() const {
    if (productionCost > 0)
        return ((price - productionCost) / productionCost) * 100;
    return 0.0;
}

void ProductBase::setPrice(double newPrice) {
    if (newPrice >= 0) price = newPrice;
}

void ProductBase::setQuantity(int newQuantity) {
    if (newQuantity >= 0) quantity = newQuantity;
}

void ProductBase::updateQuantity(int delta) {
    quantity += delta;
    if (quantity < 0) quantity = 0;
}

double ProductBase::calculateCost(int amount) const {
    if (amount <= 0) return 0.0;
    return price * amount;
}

bool ProductBase::isAvailable(int amount) const {
    return quantity >= amount;
}