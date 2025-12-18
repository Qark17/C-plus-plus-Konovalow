#include "ReportGenerator.h"
#include "ProductBase.h"
#include "Order.h"
#include "SaleRecord.h"
#include "Shop.h"
#include "Supplier.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <map>
inline std::tm safe_localtime(std::time_t time) {
    std::tm tm_info;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_info, &time);
#else
    localtime_r(&time, &tm_info);
#endif
    return tm_info;
}
double ReportGenerator::calculateProductionCost(const std::vector<Order>& orders,
    const std::vector<ProductBase*>& products) {
    double totalCost = 0.0;
    for (const auto& order : orders) {
        for (const auto& item : order.getItems()) {
            for (const auto& product : products) {
                if (product->getProductCode() == item.productCode) {
                    double unitCost = (product->getProductionCost() > 0) ?
                        product->getProductionCost() : product->getPrice() * 0.6;
                    totalCost += unitCost * item.quantity;
                    break;                }
            }
        }
    }
    return totalCost;
}
inline std::string safe_ctime(std::time_t time) {
    char buffer[26];
    std::string result(buffer);
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}
std::string ReportGenerator::formatCurrency(double amount) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << amount << " руб.";
    return ss.str();
}
std::string ReportGenerator::formatDate(std::time_t date) {
    char buffer[80];
    std::tm tm_info = safe_localtime(date);
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y", &tm_info);
    return std::string(buffer);
}
std::string ReportGenerator::generateSalesReport(const std::vector<SaleRecord>& sales,
    std::time_t start, std::time_t end) {
    std::stringstream report;
    report << "=== ОТЧЕТ О ПРОДАЖАХ ===\n";
    report << "Период: " << formatDate(start) << " - " << formatDate(end) << "\n\n";
    double totalRevenue = 0.0;
    int totalQuantity = 0;
    std::map<std::string, double> revenueByProduct;
    std::map<std::string, int> quantityByProduct;
    for (const auto& sale : sales) {
        if (sale.getSaleDate() >= start && sale.getSaleDate() <= end) {
            totalRevenue += sale.getTotalRevenue();
            totalQuantity += sale.getQuantitySold();
            revenueByProduct[sale.getProductCode()] += sale.getTotalRevenue();
            quantityByProduct[sale.getProductCode()] += sale.getQuantitySold();
        }
    }
    report << "Общая выручка: " << formatCurrency(totalRevenue) << "\n";
    report << "Общее количество проданных единиц: " << totalQuantity << "\n\n";
    if (!revenueByProduct.empty()) {
        report << "Детализация по продуктам:\n";
        report << std::left << std::setw(15) << "Код продукта"
            << std::setw(10) << "Кол-во"
            << std::setw(15) << "Выручка"
            << std::setw(15) << "Доля" << "\n";
        report << std::string(55, '-') << "\n";
        for (const auto& entry : revenueByProduct) {
            double percentage = (totalRevenue > 0) ? (entry.second / totalRevenue * 100) : 0;
            report << std::left << std::setw(15) << entry.first
                << std::right << std::setw(10) << quantityByProduct[entry.first]
                << std::setw(15) << std::fixed << std::setprecision(2) << entry.second
                << std::setw(15) << std::setprecision(1) << percentage << "%\n";
        }
    }
    else {
        report << "Нет данных о продажах за указанный период.\n";
    }
    return report.str();
}
std::string ReportGenerator::generateInventoryReport(const std::vector<ProductBase*>& products) {
    std::stringstream report;
    report << "=== ИНВЕНТАРНЫЙ ОТЧЕТ ===\n";
    report << "Всего позиций: " << products.size() << "\n\n";
    double totalValue = 0.0;
    int totalQuantity = 0;
    report << std::left << std::setw(20) << "Название"
        << std::setw(15) << "Код"
        << std::setw(10) << "Тип"
        << std::setw(10) << "Кол-во"
        << std::setw(12) << "Цена"
        << std::setw(15) << "Стоимость" << "\n";
    report << std::string(82, '-') << "\n";
    for (const auto& product : products) {
        double itemValue = product->getPrice() * product->getQuantity();
        totalValue += itemValue;
        totalQuantity += product->getQuantity();
        report << std::left << std::setw(20) << product->getName().substr(0, 19)
            << std::setw(15) << product->getProductCode()
            << std::setw(10) << product->getType()
            << std::right << std::setw(10) << product->getQuantity()
            << std::setw(12) << std::fixed << std::setprecision(2) << product->getPrice()
            << std::setw(15) << itemValue << "\n";
    }
    report << "\nИТОГО:\n";
    report << "Общее количество: " << totalQuantity << " единиц\n";
    report << "Общая стоимость: " << formatCurrency(totalValue) << "\n";
    return report.str();
}
std::string ReportGenerator::generateSupplierReport(const std::vector<Supplier>& suppliers) {
    std::stringstream report;
    report << "=== ОТЧЕТ О ПОСТАВЩИКАХ ===\n";
    report << "Всего поставщиков: " << suppliers.size() << "\n\n";

    int reliableCount = 0;
    for (const auto& supplier : suppliers) {
        if (supplier.getReliabilityRating() >= 7.0) reliableCount++;
    }
    report << "Надежных поставщиков (рейтинг ≥ 7): " << reliableCount << " из " << suppliers.size() << "\n\n";
    report << std::left << std::setw(20) << "Поставщик"
        << std::setw(20) << "Контактное лицо"
        << std::setw(15) << "Телефон"
        << std::setw(10) << "Рейтинг" << "\n";
    report << std::string(65, '-') << "\n";
    for (const auto& supplier : suppliers) {
        report << std::left << std::setw(20) << supplier.getName().substr(0, 19)
            << std::setw(20) << supplier.getContactPerson().substr(0, 19)
            << std::setw(15) << supplier.getContactInfo().substr(0, 14)
            << std::setw(10) << std::fixed << std::setprecision(1) << supplier.getReliabilityRating() << "\n";
    }
    return report.str();
}
std::string ReportGenerator::generateShopReport(const std::vector<Shop>& shops) {
    std::stringstream report;
    report << "=== ОТЧЕТ О МАГАЗИНАХ ===\n";
    report << "Всего магазинов: " << shops.size() << "\n\n";

    int regularCount = 0;
    for (const auto& shop : shops) {
        if (shop.isRegular()) regularCount++;
    }
    report << "Постоянных клиентов: " << regularCount << " из " << shops.size() << "\n\n";
    report << std::left << std::setw(20) << "Магазин"
        << std::setw(25) << "Адрес"
        << std::setw(15) << "Менеджер"
        << std::setw(10) << "Скидка"
        << std::setw(10) << "Постоянный" << "\n";
    report << std::string(80, '-') << "\n";
    for (const auto& shop : shops) {
        report << std::left << std::setw(20) << shop.getName().substr(0, 19)
            << std::setw(25) << shop.getAddress().substr(0, 24)
            << std::setw(15) << shop.getManager().substr(0, 14)
            << std::setw(10) << std::to_string((int)shop.getDiscount()) + "%"
            << std::setw(10) << (shop.isRegular() ? "Да" : "Нет") << "\n";
    }

    return report.str();
}
std::string ReportGenerator::generateProductPerformanceReport(
    const std::vector<ProductBase*>& products,
    const std::vector<SaleRecord>& sales) {
    std::stringstream report;
    report << "=== ОТЧЕТ О ПРОДУКТАХ ===\n\n";
    std::map<std::string, std::pair<int, double>> productStats;
    for (const auto& sale : sales) {
        auto& stats = productStats[sale.getProductCode()];
        stats.first += sale.getQuantitySold();
        stats.second += sale.getTotalRevenue();
    }
    report << std::left << std::setw(20) << "Продукт"
        << std::setw(15) << "Код"
        << std::setw(10) << "Тип"
        << std::setw(10) << "На складе"
        << std::setw(10) << "Продано"
        << std::setw(15) << "Выручка"
        << std::setw(15) << "Маржа" << "\n";
    report << std::string(95, '-') << "\n";
    for (const auto& product : products) {
        auto it = productStats.find(product->getProductCode());
        int sold = (it != productStats.end()) ? it->second.first : 0;
        double revenue = (it != productStats.end()) ? it->second.second : 0.0;
        double margin = (product->getProductionCost() > 0 && sold > 0) ?
            (revenue / sold - product->getProductionCost()) / product->getProductionCost() * 100 : 0.0;

        report << std::left << std::setw(20) << product->getName().substr(0, 19)
            << std::setw(15) << product->getProductCode()
            << std::setw(10) << product->getType()
            << std::right << std::setw(10) << product->getQuantity()
            << std::setw(10) << sold
            << std::setw(15) << std::fixed << std::setprecision(2) << revenue
            << std::setw(15) << std::setprecision(1) << margin << "%\n";
    }

    return report.str();
}
std::string ReportGenerator::generateMonthlyReport(std::time_t monthStart,
    const std::vector<ProductBase*>& products,
    const std::vector<Order>& orders,
    const std::vector<SaleRecord>& sales,
    const std::vector<Shop>& shops) {
    std::stringstream report;

    std::time_t monthEnd = monthStart + 30 * 24 * 60 * 60;

    report << "=== ЕЖЕМЕСЯЧНЫЙ ОТЧЕТ ===\n";
    report << "Период: " << formatDate(monthStart) << " - " << formatDate(monthEnd) << "\n\n";

    double monthlyRevenue = 0.0;
    int monthlySalesCount = 0;
    for (const auto& sale : sales) {
        if (sale.getSaleDate() >= monthStart && sale.getSaleDate() <= monthEnd) {
            monthlyRevenue += sale.getTotalRevenue();
            monthlySalesCount++;
        }
    }

    double productionCost = calculateProductionCost(orders, products);
    double profit = monthlyRevenue - productionCost;
    double margin = calculateMarginPercentage(monthlyRevenue, productionCost);

    report << "ФИНАНСОВЫЕ ПОКАЗАТЕЛИ:\n";
    report << "Выручка: " << formatCurrency(monthlyRevenue) << "\n";
    report << "Себестоимость: " << formatCurrency(productionCost) << "\n";
    report << "Прибыль: " << formatCurrency(profit) << "\n";
    report << "Маржа: " << std::fixed << std::setprecision(1) << margin << "%\n\n";
    report << "ОПЕРАЦИОННЫЕ ПОКАЗАТЕЛИ:\n";
    report << "Количество продаж: " << monthlySalesCount << "\n";
    report << "Количество магазинов-партнеров: " << shops.size() << "\n";
    report << "Количество товаров в ассортименте: " << products.size() << "\n\n";
    std::map<std::string, double> revenueByProduct;
    for (const auto& sale : sales) {
        if (sale.getSaleDate() >= monthStart && sale.getSaleDate() <= monthEnd) {
            revenueByProduct[sale.getProductCode()] += sale.getTotalRevenue();
        }
    }
    std::vector<std::pair<std::string, double>> sortedProducts(
        revenueByProduct.begin(), revenueByProduct.end());
    std::sort(sortedProducts.begin(), sortedProducts.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    if (!sortedProducts.empty()) {
        report << "ТОП ПРОДУКТОВ ПО ВЫРУЧКЕ:\n";
        int count = 0;
        for (const auto& entry : sortedProducts) {
            if (++count > 5) break;
            report << count << ". " << entry.first << ": " << formatCurrency(entry.second) << "\n";
        }
    }
    return report.str();
}
double ReportGenerator::calculateProfit(const std::vector<SaleRecord>& sales,
    const std::vector<Order>& productionOrders,
    const std::vector<ProductBase*>& products) {
    double totalRevenue = 0.0;
    for (const auto& sale : sales) {
        totalRevenue += sale.getTotalRevenue();
    }
    double totalCost = calculateProductionCost(productionOrders, products);
    return totalRevenue - totalCost;
}
double ReportGenerator::calculateMarginPercentage(double revenue, double cost) {
    if (cost == 0) return 0.0;
    return ((revenue - cost) / cost) * 100;
}