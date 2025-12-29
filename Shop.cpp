#include "Shop.h"
#include <algorithm>
Shop::Shop(const std::string& name, const std::string& address,
    const std::string& phone, const std::string& manager)
    : name(name), address(address), phone(phone), manager(manager),
    discount(0.0), isRegularCustomer(false) {
}
void Shop::placeOrder(const Order& order) {
    orders.push_back(order);
}
void Shop::cancelOrder(int orderId) {
    orders.erase(std::remove_if(orders.begin(), orders.end(),
        [orderId](const Order& order) {
            return order.getOrderId() == orderId;
        }), orders.end());
}
int Shop::getTotalOrderedQuantity() const {
    int total = 0;
    for (const auto& order : orders) {
        total += order.getTotalItemsQuantity();
    }
    return total;
}
std::vector<Order> Shop::getOrders() const {
    return orders;
}
std::string Shop::getName() const { return name; }
std::string Shop::getAddress() const { return address; }
std::string Shop::getPhone() const { return phone; }
std::string Shop::getManager() const { return manager; }
double Shop::getDiscount() const { return discount; }
bool Shop::isRegular() const { return isRegularCustomer; }
void Shop::setDiscount(double newDiscount) {
    if (newDiscount >= 0 && newDiscount <= 100) discount = newDiscount;
}
void Shop::setRegularCustomer(bool regular) {
    isRegularCustomer = regular;
}
void Shop::setManager(const std::string& newManager) {
    manager = newManager;
}
double Shop::calculateOrderTotal(double basePrice, int quantity) const {
    double total = basePrice * quantity;
    if (isRegularCustomer) {
        total -= total * (discount / 100);
    }
    return total;
}
std::string Shop::getFullInfo() const {
    std::string info = "Shop: " + name +
        "\nAddress: " + address +
        "\nPhone: " + phone +
        "\nManager: " + manager +
        "\nRegular Customer: " + (isRegularCustomer ? "Yes" : "No") +
        "\nDiscount: " + std::to_string(discount) + "%" +
        "\nTotal Orders: " + std::to_string(orders.size()) +
        "\nTotal Items Ordered: " + std::to_string(getTotalOrderedQuantity());
    if (!orders.empty()) {
        info += "\n\nOrder Details:";
        info += "\n-----------------";
        for (size_t i = 0; i < orders.size(); ++i) {
            info += "\nOrder #" + std::to_string(orders[i].getOrderId()) +
                ": " + orders[i].getOrderInfo();
            const auto& items = orders[i].getItems();
            for (const auto& item : items) {
                std::string productCode = item.product ?
                    item.product->getProductCode() :
                    "Unknown";
                info += "\n  - " + productCode +
                    " x" + std::to_string(item.quantity) +
                    " @ " + std::to_string(item.unitPrice) + " each";
            }
            if (i < orders.size() - 1) info += "\n";        }
    }
    return info;
}