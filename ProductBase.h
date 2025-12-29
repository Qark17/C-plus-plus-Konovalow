#pragma once // все ПРОДУКТЫ
#include <string>
#include <memory>
#include <vector>
class ProductBase {
protected:
    std::string name;
    std::string productCode;
    double price;
    int quantity;
    double productionCost;
public:
    ProductBase(const std::string& name, const std::string& code,
        double price, int quantity, double cost = 0.0);
    virtual ~ProductBase() = default;
    /// @brief Возвращает описание продукта
    virtual std::string getDescription() const;
    /// @brief Возвращает тип продукта (чисто виртуальный метод)
    virtual std::string getType() const = 0;
    std::string getName() const;
    std::string getProductCode() const;
    double getPrice() const;
    int getQuantity() const;
    double getProductionCost() const;
    double getProfitMargin() const;
    void setPrice(double newPrice);
    void setQuantity(int newQuantity);
    void updateQuantity(int delta);
    double calculateCost(int amount) const;
    bool isAvailable(int amount = 1) const;
};