#pragma once// Фиксация ФАКТА ПРОДАЖИ
#include <string>
#include <ctime>
class SaleRecord {
private:
    std::string productCode;
    int quantitySold;
    double totalRevenue;
    std::time_t saleDate;
    std::string shopName;
public:
    SaleRecord(const std::string& product, int quantity,
        double revenue, const std::string& shop = "");
    std::string getProductCode() const;
    int getQuantitySold() const;
    double getTotalRevenue() const;
    std::time_t getSaleDate() const;
    std::string getShopName() const;
    void setShopName(const std::string& shop);
    std::string getSaleInfo() const;
};