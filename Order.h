#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <memory>
// @brief Структура для позиции в заказе
struct OrderItem {
    std::string productCode;
    int quantity;
    double unitPrice;
    OrderItem(const std::string& code, int qty, double price)
        : productCode(code), quantity(qty), unitPrice(price) {
    }
    // @brief Рассчитывает стоимость позиции
    double getItemTotal() const {
        return quantity * unitPrice;
    }
};
// @brief Класс для представления заказа на производство
class Order {
private:
    static int nextOrderId;
    int orderId;
    std::string shopName;
    std::vector<OrderItem> items;
    std::time_t orderDate;
    std::time_t deliveryDate;
    std::string status;
    double totalPrice;
    bool isPaid;
public:
    Order(const std::string& shop);
    Order(const std::string& shop, const std::string& productCode,
        int quantity, double unitPrice);
    Order(const std::string& shop, const std::vector<OrderItem>& orderItems);
    int getOrderId() const;
    std::string getShopName() const;
    std::string getStatus() const;
    void setStatus(const std::string& newStatus);
    std::time_t getOrderDate() const;
    std::time_t getDeliveryDate() const;
    void setDeliveryDate(std::time_t date);
    double getTotalPrice() const;
    bool isPaidOrder() const;
    void markAsPaid();
    bool isDelivered() const;
    bool isOverdue() const;
    int getDaysSinceOrder() const;
    std::string getOrderInfo() const;
    void addItem(const std::string& productCode, int quantity, double unitPrice);
    void addItem(const OrderItem& item);
    bool removeItem(const std::string& productCode);
    bool updateItemQuantity(const std::string& productCode, int newQuantity);
    const std::vector<OrderItem>& getItems() const;
    int getItemCount() const;
    int getTotalItemsQuantity() const;
    OrderItem* findItem(const std::string& productCode);
    bool containsItem(const std::string& productCode) const;
    void clearItems();
    void recalculateTotal();
    std::string getDetailedInfo() const;
};