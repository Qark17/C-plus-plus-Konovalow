#pragma once //ПРОДАЖИ
#include <vector>
#include <memory>
#include <string>
#include <ctime>
#include "Shop.h"
#include "Order.h"
#include "SaleRecord.h"
class SalesManager {
private:
    std::vector<Shop> shops;
    std::vector<Order> orders;
    std::vector<SaleRecord> sales;
public:
    void addShop(const Shop& shop);
    void addOrder(const Order& order);
    void addSale(const SaleRecord& sale);
    std::vector<Shop> getShopsByProduct(const std::string& productCode) const;
    Shop* findShopByName(const std::string& name);
    std::vector<Order> getOrdersByShop(const std::string& shopName) const;
    std::vector<Order> getOrdersByProduct(const std::string& productCode) const;
    std::vector<Order> getOrdersByPeriod(std::time_t start, std::time_t end) const;
    std::vector<Order> getPendingOrders() const;
    std::vector<Order> getOverdueOrders() const;
    std::vector<SaleRecord> getSalesByPeriod(std::time_t start, std::time_t end) const;
    std::vector<SaleRecord> getSalesByProduct(const std::string& productCode) const;
    std::vector<SaleRecord> getSalesByShop(const std::string& shopName) const;
    double calculateTotalRevenue(std::time_t start, std::time_t end) const;
    int calculateTotalQuantitySold(const std::string& productCode,
        std::time_t start, std::time_t end) const;
    void processOrder(int orderId, const std::string& newStatus);
    void markOrderAsDelivered(int orderId, std::time_t deliveryDate);
    std::vector<std::string> getShopNames() const;
};