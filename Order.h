#pragma once
#include <string>
#include <ctime>
#include <memory>

/// @brief Класс для представления заказа на производство
/// @details Содержит информацию о заказе, его статусе и сроках
class Order {
private:
    static int nextOrderId;

    int orderId;
    std::string shopName;
    std::string productCode;
    int quantity;
    std::time_t orderDate;
    std::time_t deliveryDate;
    std::string status;
    double totalPrice;
    bool isPaid;

public:
    /// @brief Конструктор заказа
    Order(const std::string& shop, const std::string& product,
        int qty, double unitPrice);

    int getOrderId() const;
    std::string getShopName() const;
    std::string getProductCode() const;
    int getQuantity() const;
    std::time_t getOrderDate() const;
    std::time_t getDeliveryDate() const;
    std::string getStatus() const;
    double getTotalPrice() const;
    bool isPaidOrder() const;

    void setStatus(const std::string& newStatus);
    void setDeliveryDate(std::time_t date);
    void markAsPaid();
    void updateQuantity(int newQuantity, double unitPrice);

    bool isDelivered() const;
    bool isOverdue() const;
    int getDaysSinceOrder() const;
    std::string getOrderInfo() const;
};