#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>
/// @brief Класс для представления магазина-партнера
/// @details Содержит информацию о магазине и его заказах
class Shop {
private:
    std::string name;
    std::string address;
    std::string phone;
    std::string manager;
    std::vector<std::pair<std::string, int>> orders;
    std::vector<std::string> products;
    std::vector<std::string> suppliers;
    double discount;
    bool isRegularCustomer;
public:
    Shop(const std::string& name, const std::string& address,
        const std::string& phone = "", const std::string& manager = "");
    void placeOrder(const std::string& productCode, int quantity);
    void cancelOrder(const std::string& productCode);
    int getTotalOrderedQuantity() const;
    std::vector<std::pair<std::string, int>> getOrders() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::string getManager() const;
    double getDiscount() const;
    bool isRegular() const;
    void setDiscount(double discount);
    void setRegularCustomer(bool regular);
    void setManager(const std::string& manager);
    double calculateOrderTotal(double basePrice, int quantity) const;
    std::string getFullInfo() const;
};