#pragma once
#include <string>
#include <ctime>

/// @brief Класс для хранения информации о продажах
/// @details Содержит данные о количестве проданного товара, выручке, дате продажи и магазине
class SaleRecord {
private:
    std::string productCode;
    int quantitySold;
    double totalRevenue;
    std::time_t saleDate;
    std::string shopName;

public:
    /// @brief Конструктор записи о продаже
    /// @param product Код продукта
    /// @param quantity Количество проданных единиц
    /// @param revenue Общая выручка от продажи
    /// @param shop Название магазина (по умолчанию пустая строка)
    SaleRecord(const std::string& product, int quantity,
        double revenue, const std::string& shop = "");

    /// @brief Возвращает код продукта
    std::string getProductCode() const;

    /// @brief Возвращает количество проданных единиц
    int getQuantitySold() const;

    /// @brief Возвращает общую выручку от продажи
    double getTotalRevenue() const;

    /// @brief Возвращает дату продажи
    std::time_t getSaleDate() const;

    /// @brief Возвращает название магазина
    std::string getShopName() const;

    /// @brief Устанавливает название магазина
    /// @param shop Новое название магазина
    void setShopName(const std::string& shop);

    /// @brief Возвращает информацию о продаже в виде строки
    std::string getSaleInfo() const;
};