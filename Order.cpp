#include "Order.h"
#include <ctime>
#include <chrono>
int Order::nextOrderId = 1000;
inline std::string safe_ctime(std::time_t time) {
    char buffer[26];
#if defined(_WIN32) || defined(_WIN64)
    ctime_s(buffer, sizeof(buffer), &time);
#else
    ctime_r(&time, buffer);
#endif
    std::string result(buffer);
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}
Order::Order(const std::string& shop, const std::string& product,
    int qty, double unitPrice)
    : shopName(shop), productCode(product), quantity(qty),
    totalPrice(unitPrice* qty), isPaid(false)
{
    orderId = nextOrderId++;
    orderDate = std::time(nullptr);
    deliveryDate = 0;
    status = "pending";
    if (quantity <= 0) quantity = 1;
    if (totalPrice < 0) totalPrice = 0;
}
int Order::getOrderId() const { return orderId; }
std::string Order::getShopName() const { return shopName; }
std::string Order::getProductCode() const { return productCode; }
int Order::getQuantity() const { return quantity; }
std::time_t Order::getOrderDate() const { return orderDate; }
std::time_t Order::getDeliveryDate() const { return deliveryDate; }
std::string Order::getStatus() const { return status; }
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
void Order::updateQuantity(int newQuantity, double unitPrice) {
    if (newQuantity > 0) {
        quantity = newQuantity;
        totalPrice = unitPrice * quantity;
    }
}
bool Order::isDelivered() const {
    return status == "delivered";
}
bool Order::isOverdue() const {
    if (deliveryDate == 0 || status == "delivered" || status == "cancelled") {
        return false;
    }
    std::time_t now = std::time(nullptr);
    return now > deliveryDate;
}
int Order::getDaysSinceOrder() const {
    std::time_t now = std::time(nullptr);
    double seconds = difftime(now, orderDate);
    return static_cast<int>(seconds / (60 * 60 * 24));
}
std::string Order::getOrderInfo() const {
    std::string info = "Order #" + std::to_string(orderId) +
        "\nShop: " + shopName +
        "\nProduct: " + productCode +
        "\nQuantity: " + std::to_string(quantity) +
        "\nTotal: " + std::to_string(totalPrice) +
        "\nStatus: " + status +
        "\nPaid: " + (isPaid ? "Yes" : "No") +
        "\nOrder Date: " + safe_ctime(orderDate);
    if (deliveryDate != 0) {
        info += "\nDelivery Date: " + safe_ctime(deliveryDate);
    }
    if (isOverdue()) {
        info += "\nError!";
    }
    return info;
}