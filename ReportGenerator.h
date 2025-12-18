#pragma once
#include <string>
#include <vector>
#include <ctime>

// Предварительные объявления для избежания циклических зависимостей
class ProductBase;
class Order;
class SaleRecord;
class Shop;
class Supplier;

/// @brief Класс для генерации различных отчетов кондитерской фабрики
/// @details Содержит статические методы для создания финансовых, 
///          инвентарных и аналитических отчетов
class ReportGenerator {
public:
    /// @brief Рассчитывает стоимость произведенного товара за период
    /// @param orders Список заказов на производство
    /// @param products Список всех продуктов
    /// @return Общая стоимость производства
    static double calculateProductionCost(const std::vector<Order>& orders,
        const std::vector<ProductBase*>& products);

    /// @brief Генерирует отчет о продажах за указанный период
    /// @param sales Записи о продажах
    /// @param start Начало периода
    /// @param end Конец периода
    /// @return Форматированный отчет в виде строки
    static std::string generateSalesReport(const std::vector<SaleRecord>& sales,
        std::time_t start, std::time_t end);

    /// @brief Генерирует инвентарный отчет
    /// @param products Список продуктов
    /// @return Форматированный отчет в виде строки
    static std::string generateInventoryReport(const std::vector<ProductBase*>& products);

    /// @brief Генерирует отчет о поставщиках
    /// @param suppliers Список поставщиков
    /// @return Форматированный отчет в виде строки
    static std::string generateSupplierReport(const std::vector<Supplier>& suppliers);

    /// @brief Генерирует отчет о магазинах
    /// @param shops Список магазинов
    /// @return Форматированный отчет в виде строки
    static std::string generateShopReport(const std::vector<Shop>& shops);

    /// @brief Генерирует отчет о производительности продуктов
    /// @param products Список продуктов
    /// @param sales Записи о продажах
    /// @return Форматированный отчет в виде строки
    static std::string generateProductPerformanceReport(
        const std::vector<ProductBase*>& products,
        const std::vector<SaleRecord>& sales);

    /// @brief Генерирует ежемесячный отчет
    /// @param monthStart Начало месяца
    /// @param products Список продуктов
    /// @param orders Список заказов
    /// @param sales Записи о продажах
    /// @param shops Список магазинов
    /// @return Форматированный отчет в виде строки
    static std::string generateMonthlyReport(std::time_t monthStart,
        const std::vector<ProductBase*>& products,
        const std::vector<Order>& orders,
        const std::vector<SaleRecord>& sales,
        const std::vector<Shop>& shops);

    /// @brief Рассчитывает прибыль за период
    /// @param sales Записи о продажах
    /// @param productionOrders Заказы на производство
    /// @param products Список продуктов
    /// @return Общая прибыль
    static double calculateProfit(const std::vector<SaleRecord>& sales,
        const std::vector<Order>& productionOrders,
        const std::vector<ProductBase*>& products);

    /// @brief Рассчитывает процент маржи
    /// @param revenue Выручка
    /// @param cost Себестоимость
    /// @return Процент маржи
    static double calculateMarginPercentage(double revenue, double cost);

    /// @brief Форматирует денежную сумму
    /// @param amount Сумма
    /// @return Отформатированная строка с валютой
    static std::string formatCurrency(double amount);

    /// @brief Форматирует дату
    /// @param date Временная метка
    /// @return Отформатированная дата в виде строки
    static std::string formatDate(std::time_t date);
};