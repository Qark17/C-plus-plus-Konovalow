#pragma once// МАГАЗИНЫ
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "Order.h"
class Shop {
private:
    std::string name;
    std::string address;
    std::string phone;
    std::string manager;
    std::vector<Order> orders;
    std::vector<std::string> products;
    std::vector<std::string> suppliers;
    double discount;
    bool isRegularCustomer;
public:
    Shop(const std::string& name, const std::string& address,
        const std::string& phone = "", const std::string& manager = "");
    void placeOrder(const Order& order);
    void cancelOrder(int orderId);
    int getTotalOrderedQuantity() const;
    std::vector<Order> getOrders() const;    
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