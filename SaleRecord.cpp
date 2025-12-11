#include "SaleRecord.h"
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
SaleRecord::SaleRecord(const std::string& product, int quantity,
    double revenue, const std::string& shop)
    : productCode(product), quantitySold(quantity),
    totalRevenue(revenue), shopName(shop)
{
    saleDate = std::time(nullptr);
}
std::string SaleRecord::getProductCode() const { return productCode; }
int SaleRecord::getQuantitySold() const { return quantitySold; }
double SaleRecord::getTotalRevenue() const { return totalRevenue; }
std::time_t SaleRecord::getSaleDate() const { return saleDate; }
std::string SaleRecord::getShopName() const { return shopName; }
void SaleRecord::setShopName(const std::string& shop) {
    shopName = shop;
}
std::string SaleRecord::getSaleInfo() const {
    return "Product: " + productCode +
        ", Quantity: " + std::to_string(quantitySold) +
        ", Revenue: " + std::to_string(totalRevenue) +
        ", Shop: " + shopName +
        ", Date: " + safe_ctime(saleDate);
}