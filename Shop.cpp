#include "Shop.h"
#include <algorithm>

Shop::Shop(const std::string& name, const std::string& address,
    const std::string& phone, const std::string& manager)
    : name(name), address(address), phone(phone), manager(manager),
    discount(0.0), isRegularCustomer(false) {
}

void Shop::placeOrder(const std::string& productCode, int quantity) {
    if (quantity <= 0) return;

    for (auto& order : orders) {
        if (order.first == productCode) {
            order.second += quantity;
            return;
        }
    }

    orders.push_back(std::make_pair(productCode, quantity));
}

void Shop::cancelOrder(const std::string& productCode) {
    orders.erase(std::remove_if(orders.begin(), orders.end(),
        [&productCode](const std::pair<std::string, int>& order) {
            return order.first == productCode;
        }), orders.end());
}

int Shop::getTotalOrderedQuantity() const {
    int total = 0;
    for (const auto& order : orders) {
        total += order.second;
    }
    return total;
}

std::vector<std::pair<std::string, int>> Shop::getOrders() const {
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
        "\nTotal Orders: " + std::to_string(getTotalOrderedQuantity()) +
        "\nOrders: ";

    for (size_t i = 0; i < orders.size(); ++i) {
        info += orders[i].first + " x" + std::to_string(orders[i].second);
        if (i < orders.size() - 1) info += ", ";
    }

    return info;
}