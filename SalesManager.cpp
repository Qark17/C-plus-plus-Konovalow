#include "SalesManager.h"
#include <algorithm>

void SalesManager::addShop(const Shop& shop) {
    shops.push_back(shop);
}

void SalesManager::addOrder(const Order& order) {
    orders.push_back(order);
}

void SalesManager::addSale(const SaleRecord& sale) {
    sales.push_back(sale);
}

std::vector<Shop> SalesManager::getShopsByProduct(const std::string& productCode) const {
    std::vector<Shop> result;
    std::vector<std::string> shopNames;
    for (const auto& order : orders) {
        if (order.getProductCode() == productCode) {
            shopNames.push_back(order.getShopName());
        }
    }
    std::sort(shopNames.begin(), shopNames.end());
    shopNames.erase(std::unique(shopNames.begin(), shopNames.end()), shopNames.end());
    for (const auto& shopName : shopNames) {
        for (const auto& shop : shops) {
            if (shop.getName() == shopName) {
                result.push_back(shop);
                break;
            }
        }
    }
    return result;
}
Shop* SalesManager::findShopByName(const std::string& name) {
    for (auto& shop : shops) {
        if (shop.getName() == name)
            return &shop;
    }
    return nullptr;
}

std::vector<Order> SalesManager::getOrdersByShop(const std::string& shopName) const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getShopName() == shopName)
            result.push_back(order);
    }
    return result;
}

std::vector<Order> SalesManager::getOrdersByProduct(const std::string& productCode) const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getProductCode() == productCode)
            result.push_back(order);
    }
    return result;
}

std::vector<Order> SalesManager::getOrdersByPeriod(std::time_t start, std::time_t end) const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getOrderDate() >= start && order.getOrderDate() <= end)
            result.push_back(order);
    }
    return result;
}

std::vector<Order> SalesManager::getPendingOrders() const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.getStatus() == "pending" || order.getStatus() == "processing")
            result.push_back(order);
    }
    return result;
}

std::vector<Order> SalesManager::getOverdueOrders() const {
    std::vector<Order> result;
    for (const auto& order : orders) {
        if (order.isOverdue())
            result.push_back(order);
    }
    return result;
}

std::vector<SaleRecord> SalesManager::getSalesByPeriod(std::time_t start, std::time_t end) const {
    std::vector<SaleRecord> result;
    for (const auto& sale : sales) {
        if (sale.getSaleDate() >= start && sale.getSaleDate() <= end)
            result.push_back(sale);
    }
    return result;
}

std::vector<SaleRecord> SalesManager::getSalesByProduct(const std::string& productCode) const {
    std::vector<SaleRecord> result;
    for (const auto& sale : sales) {
        if (sale.getProductCode() == productCode)
            result.push_back(sale);
    }
    return result;
}

std::vector<SaleRecord> SalesManager::getSalesByShop(const std::string& shopName) const {
    std::vector<SaleRecord> result;
    for (const auto& sale : sales) {
        if (sale.getShopName() == shopName)
            result.push_back(sale);
    }
    return result;
}

double SalesManager::calculateTotalRevenue(std::time_t start, std::time_t end) const {
    double total = 0.0;
    for (const auto& sale : sales) {
        if (sale.getSaleDate() >= start && sale.getSaleDate() <= end)
            total += sale.getTotalRevenue();
    }
    return total;
}

int SalesManager::calculateTotalQuantitySold(const std::string& productCode,
    std::time_t start, std::time_t end) const {
    int total = 0;
    for (const auto& sale : sales) {
        if (sale.getProductCode() == productCode &&
            sale.getSaleDate() >= start && sale.getSaleDate() <= end) {
            total += sale.getQuantitySold();
        }
    }
    return total;
}

void SalesManager::processOrder(int orderId, const std::string& newStatus) {
    for (auto& order : orders) {
        if (order.getOrderId() == orderId) {
            order.setStatus(newStatus);
            break;
        }
    }
}

void SalesManager::markOrderAsDelivered(int orderId, std::time_t deliveryDate) {
    for (auto& order : orders) {
        if (order.getOrderId() == orderId) {
            order.setStatus("delivered");
            order.setDeliveryDate(deliveryDate);
            break;
        }
    }
}

std::vector<std::string> SalesManager::getShopNames() const {
    std::vector<std::string> names;
    for (const auto& shop : shops) {
        names.push_back(shop.getName());
    }
    return names;
}