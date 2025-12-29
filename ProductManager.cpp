#include "ProductManager.h"
#include <algorithm>
#include <cctype>
#include <functional>
#include <stdexcept>

void ProductManager::addProduct(std::unique_ptr<ProductBase> product) {
    if (findProductByCode(product->getProductCode()) != nullptr) {
        throw std::runtime_error("Product with code " + product->getProductCode() + " already exists");
    }
    products.push_back(std::move(product));
}

void ProductManager::removeProduct(const std::string& productCode) {
    auto it = std::remove_if(products.begin(), products.end(),
        [&productCode](const std::unique_ptr<ProductBase>& p) {
            return p->getProductCode() == productCode;
        });
    products.erase(it, products.end());
}

ProductBase* ProductManager::findProductByCode(const std::string& productCode) const {
    auto it = std::find_if(products.begin(), products.end(),
        [&productCode](const std::unique_ptr<ProductBase>& p) {
            return p->getProductCode() == productCode;
        });
    return (it != products.end()) ? it->get() : nullptr;
}

ProductBase* ProductManager::findProductByName(const std::string& name) const {
    auto it = std::find_if(products.begin(), products.end(),
        [&name](const std::unique_ptr<ProductBase>& p) {
            return p->getName() == name;
        });
    return (it != products.end()) ? it->get() : nullptr;
}

std::vector<ProductBase*> ProductManager::getAllProducts() const {
    std::vector<ProductBase*> result;
    for (const auto& p : products)
        result.push_back(p.get());
    return result;
}

std::vector<ProductBase*> ProductManager::getProductsByType(const std::string& type) const {
    std::vector<ProductBase*> result;
    for (const auto& p : products) {
        if (p->getType() == type)
            result.push_back(p.get());
    }
    return result;
}

std::vector<ProductBase*> ProductManager::getAvailableProducts(int minQuantity) const {
    std::vector<ProductBase*> result;
    for (const auto& p : products) {
        if (p->getQuantity() >= minQuantity)
            result.push_back(p.get());
    }
    return result;
}

std::vector<std::pair<std::string, double>> ProductManager::getProductAssortment() const {
    std::vector<std::pair<std::string, double>> assortment;
    for (const auto& p : products) {
        assortment.push_back(std::make_pair(p->getName(), p->getPrice()));
    }
    return assortment;
}

ProductBase* ProductManager::getMostPopularProduct() const {
    if (salesCounter.empty() || products.empty()) {
        auto it = std::max_element(products.begin(), products.end(),
            [](const std::unique_ptr<ProductBase>& a, const std::unique_ptr<ProductBase>& b) {
                return a->getQuantity() < b->getQuantity();
            });
        return (it != products.end()) ? it->get() : nullptr;
    }

    std::string mostPopularCode;
    int maxSales = -1;

    for (const auto& entry : salesCounter) {
        if (entry.second > maxSales) {
            maxSales = entry.second;
            mostPopularCode = entry.first;
        }
    }

    return findProductByCode(mostPopularCode);
}

void ProductManager::recordSale(const std::string& productCode, int quantity) {
    salesCounter[productCode] += quantity;

    auto product = findProductByCode(productCode);
    if (product) {
        product->updateQuantity(-quantity);
    }
}

int ProductManager::getSalesCount(const std::string& productCode) const {
    auto it = salesCounter.find(productCode);
    return (it != salesCounter.end()) ? it->second : 0;
}

double ProductManager::getTotalInventoryValue() const {
    double total = 0.0;
    for (const auto& p : products) {
        total += p->getPrice() * p->getQuantity();
    }
    return total;
}

std::vector<ProductBase*> ProductManager::getLowStockProducts(int threshold) const {
    std::vector<ProductBase*> result;
    for (const auto& p : products) {
        if (p->getQuantity() < threshold)
            result.push_back(p.get());
    }
    return result;
}

std::vector<ProductBase*> ProductManager::searchProducts(const std::string& keyword) const {
    std::vector<ProductBase*> result;
    if (keyword.empty()) return result;

    std::string keywordLower = keyword;
    std::transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(),
        [](unsigned char c) { return std::tolower(c); });

    for (const auto& p : products) {
        std::string nameLower = p->getName();
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(),
            [](unsigned char c) { return std::tolower(c); });

        std::string typeLower = p->getType();
        std::transform(typeLower.begin(), typeLower.end(), typeLower.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (nameLower.find(keywordLower) != std::string::npos ||
            typeLower.find(keywordLower) != std::string::npos ||
            p->getProductCode().find(keyword) != std::string::npos) {
            result.push_back(p.get());
        }
    }

    return result;
}