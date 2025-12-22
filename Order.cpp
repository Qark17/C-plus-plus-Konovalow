#include "Order.h"
#include <chrono>
#include <algorithm>
#include "ReportGenerator.h"
#include "SaleRecord.h"
#include <ctime>
int Order::nextOrderId = 1000;
Order::Order(const std::string& shop)
    : shopName(shop), totalPrice(0.0), isPaid(false) {
    orderId = nextOrderId++;
    orderDate = std::time(nullptr);
    deliveryDate = 0;
    status = "pending";
}
Order::Order(const std::string& shop, const std::shared_ptr<ProductBase>& product,
    int quantity, double unitPrice)
    : shopName(shop), totalPrice(0.0), isPaid(false) {
    orderId = nextOrderId++;
    orderDate = std::time(nullptr);
    deliveryDate = 0;
    status = "pending";
    if (quantity > 0 && unitPrice >= 0 && product) {
        items.emplace_back(product, quantity, unitPrice);
        recalculateTotal();    }
}
Order::Order(const std::string& shop, const std::vector<OrderItem>& orderItems)
    : shopName(shop), items(orderItems), totalPrice(0.0), isPaid(false) {
    orderId = nextOrderId++;
    orderDate = std::time(nullptr);
    deliveryDate = 0;
    status = "pending";
    items.erase(std::remove_if(items.begin(), items.end(),
        [](const OrderItem& item) {
            return item.quantity <= 0 || item.unitPrice < 0 || !item.product;
        }), items.end());
    recalculateTotal();
}
int Order::getOrderId() const { return orderId; }
std::string Order::getShopName() const { return shopName; }
std::string Order::getStatus() const { return status; }
std::time_t Order::getOrderDate() const { return orderDate; }
std::time_t Order::getDeliveryDate() const { return deliveryDate; }
double Order::getTotalPrice() const { return totalPrice; }
bool Order::isPaidOrder() const { return isPaid; }
void Order::setStatus(const std::string& newStatus) {
    status = newStatus;
}
void Order::setDeliveryDate(std::time_t date) {
    deliveryDate = date;
}
void Order::markAsPaid() {
    isPaid = true;
}
bool Order::isDelivered() const {
    return status == "delivered";
}
bool Order::isOverdue() const {
    if (deliveryDate == 0 || status == "delivered" || status == "cancelled") {
        return false;    }
    std::time_t now = std::time(nullptr);
    return now > deliveryDate;
}
int Order::getDaysSinceOrder() const {
    std::time_t now = std::time(nullptr);
    double seconds = difftime(now, orderDate);
    return static_cast<int>(seconds / (60 * 60 * 24));
}
std::string Order::getOrderInfo() const {
    std::string info = "Заказ #" + std::to_string(orderId) +
        "\nМагазин: " + shopName + "\nДата заказа: " + safe_ctime(orderDate) +
        "\nСтатус: " + status + "\nОплачен: " + (isPaid ? "Да" : "Нет") +
        "\nКоличество позиций: " + std::to_string(getItemCount()) +
        "\nОбщее количество товаров: " + std::to_string(getTotalItemsQuantity()) +
        "\nОбщая стоимость: " + std::to_string(totalPrice) + " руб.";
    if (deliveryDate != 0) {
        info += "\nДата доставки: " + safe_ctime(deliveryDate);    }
    if (isOverdue()) {
        info += "\nПРОСРОЧЕН!";    }
    return info;
}
void Order::addItem(const std::shared_ptr<ProductBase>& product, int quantity, double unitPrice) {
    if (quantity <= 0 || unitPrice < 0 || !product) return;
    for (auto& item : items) {
        if (item.product && item.product->getProductCode() == product->getProductCode()) {
            item.quantity += quantity;
            recalculateTotal();
            return;        }
    }
    items.emplace_back(product, quantity, unitPrice);
    recalculateTotal();
}
void Order::addItem(const OrderItem& item) {
    if (item.quantity <= 0 || item.unitPrice < 0 || !item.product) return;
    for (auto& existingItem : items) {
        if (existingItem.product && item.product &&
            existingItem.product->getProductCode() == item.product->getProductCode()) {
            existingItem.quantity += item.quantity;
            recalculateTotal();
            return;        }
    }
    items.push_back(item);
    recalculateTotal();
}
bool Order::removeItem(const std::string& productCode) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&productCode](const OrderItem& item) {
            return item.product && item.product->getProductCode() == productCode;
        });
    if (it != items.end()) {
        items.erase(it, items.end());
        recalculateTotal();
        return true;
    }
    return false;
}
bool Order::updateItemQuantity(const std::string& productCode, int newQuantity) {
    if (newQuantity <= 0) {
        return removeItem(productCode);
    }
    for (auto& item : items) {
        if (item.product && item.product->getProductCode() == productCode) {
            item.quantity = newQuantity;
            recalculateTotal();
            return true;        }
    }
    return false;
}
const std::vector<OrderItem>& Order::getItems() const {
    return items;
}
int Order::getItemCount() const {
    return static_cast<int>(items.size());
}
int Order::getTotalItemsQuantity() const {
    int total = 0;
    for (const auto& item : items) {
        total += item.quantity;    }
    return total;
}
OrderItem* Order::findItem(const std::shared_ptr<ProductBase>& product) {
    if (!product) return nullptr;

    for (auto& item : items) {
        if (item.product && item.product->getProductCode() == product->getProductCode()) {
            return &item;        }
    }
    return nullptr;
}
OrderItem* Order::findItem(const std::string& productCode) {
    for (auto& item : items) {
        if (item.product && item.product->getProductCode() == productCode) {
            return &item;
        }
    }
    return nullptr;
}
bool Order::containsItem(const std::shared_ptr<ProductBase>& product) const {
    if (!product) return false;

    for (const auto& item : items) {
        if (item.product && item.product->getProductCode() == product->getProductCode()) {
            return true;        }
    }
    return false;
}
bool Order::containsItem(const std::string& productCode) const {
    for (const auto& item : items) {
        if (item.product && item.product->getProductCode() == productCode) {
            return true;        }
    }
    return false;
}
void Order::clearItems() {
    items.clear();
    recalculateTotal();
}
void Order::recalculateTotal() {
    totalPrice = 0.0;
    for (const auto& item : items) {
        totalPrice += item.getItemTotal();
    }
    if (totalPrice < 0) {
        totalPrice = 0.0;
    }
}
std::string Order::getDetailedInfo() const {
    std::string info = getOrderInfo();
    if (!items.empty()) {
        info += "\n\nСостав заказа:";
        info += "\n-----------------";
        int counter = 1;
        for (const auto& item : items) {
            std::string productName = item.product ? item.product->getName() : "Неизвестный товар";
            std::string productCode = item.product ? item.product->getProductCode() : "N/A";
            info += "\n" + std::to_string(counter++) + ". " + productName +
                " [Код: " + productCode + "]" +
                " x" + std::to_string(item.quantity) +
                " (по " + std::to_string(item.unitPrice) + " руб.) = " +
                std::to_string(item.getItemTotal()) + " руб.";        }
    }
    return info;
}