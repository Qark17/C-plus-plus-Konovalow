#pragma once// ПРЕОБРАЗОВАНИЕ данных в полезную информацию
#include <string>
#include <vector>
#include <ctime>
class ProductBase;
class Order;
class SaleRecord;
class Shop;
class Supplier;
// @brief Класс для генерации различных отчетов кондитерской фабрики
// @details Содержит статические методы для создания отчетов
class ReportGenerator {
public:
    // @brief Рассчитывает стоимость произведенного товара за период
    static double calculateProductionCost(const std::vector<Order>& orders,
        const std::vector<ProductBase*>& products);
    // @brief Генерирует отчет о продажах за указанный период
    static std::string generateSalesReport(const std::vector<SaleRecord>& sales,
        std::time_t start, std::time_t end);
    // @brief Генерирует инвентарный отчет
    static std::string generateInventoryReport(const std::vector<ProductBase*>& products);
    // @brief Генерирует отчет о поставщиках
    static std::string generateSupplierReport(const std::vector<Supplier>& suppliers);
    // @brief Генерирует отчет о магазинах
    static std::string generateShopReport(const std::vector<Shop>& shops);
    // @brief Генерирует отчет о производительности продуктов
    static std::string generateProductPerformanceReport(
        const std::vector<ProductBase*>& products,
        const std::vector<SaleRecord>& sales);
    // @brief Генерирует ежемесячный отчет
    static std::string generateMonthlyReport(std::time_t monthStart,
        const std::vector<ProductBase*>& products,
        const std::vector<Order>& orders,
        const std::vector<SaleRecord>& sales,
        const std::vector<Shop>& shops);
    // @brief Рассчитывает прибыль за период
    static double calculateProfit(const std::vector<SaleRecord>& sales,
        const std::vector<Order>& productionOrders,
        const std::vector<ProductBase*>& products);
    // @brief Рассчитывает процент маржи
    static double calculateMarginPercentage(double revenue, double cost);
    /// @brief Форматирует денежную сумму
    static std::string formatCurrency(double amount);
    // @brief Форматирует дату
    static std::string formatDate(std::time_t date);
};