#include "SupplyManager.h"
#include <algorithm>

void SupplyManager::addSupplier(const Supplier& supplier) {
    suppliers.push_back(supplier);
}

void SupplyManager::addIngredient(const Ingredient& ingredient) {
    ingredients.push_back(ingredient);
}

void SupplyManager::associateIngredientWithSupplier(const std::string& ingredientName,
    const std::string& supplierName) {
    for (auto& supplier : suppliers) {
        if (supplier.getName() == supplierName) {
            supplier.addIngredient(ingredientName);
            break;
        }
    }

    supplierToIngredients[supplierName].push_back(ingredientName);
    ingredientToSuppliers[ingredientName].push_back(supplierName);
}

std::vector<Ingredient> SupplyManager::getIngredientsBySupplier(const std::string& supplierName) const {
    std::vector<Ingredient> result;
    auto it = supplierToIngredients.find(supplierName);
    if (it != supplierToIngredients.end()) {
        for (const auto& ingredientName : it->second) {
            for (const auto& ingredient : ingredients) {
                if (ingredient.getName() == ingredientName) {
                    result.push_back(ingredient);
                    break;
                }
            }
        }
    }
    return result;
}

Supplier* SupplyManager::findSupplierByName(const std::string& name) {
    for (auto& supplier : suppliers) {
        if (supplier.getName() == name)
            return &supplier;
    }
    return nullptr;
}

Ingredient* SupplyManager::findIngredientByName(const std::string& name) {
    for (auto& ingredient : ingredients) {
        if (ingredient.getName() == name)
            return &ingredient;
    }
    return nullptr;
}

std::vector<Supplier> SupplyManager::getSuppliersByIngredient(const std::string& ingredientName) const {
    std::vector<Supplier> result;
    auto it = ingredientToSuppliers.find(ingredientName);
    if (it != ingredientToSuppliers.end()) {
        for (const auto& supplierName : it->second) {
            for (const auto& supplier : suppliers) {
                if (supplier.getName() == supplierName) {
                    result.push_back(supplier);
                    break;
                }
            }
        }
    }
    return result;
}

std::vector<Supplier> SupplyManager::getReliableSuppliers(double minRating) const {
    std::vector<Supplier> result;
    for (const auto& supplier : suppliers) {
        if (supplier.getReliabilityRating() >= minRating)
            result.push_back(supplier);
    }
    return result;
}

std::vector<Ingredient> SupplyManager::getLowStockIngredients() const {
    std::vector<Ingredient> result;
    for (const auto& ingredient : ingredients) {
        if (ingredient.isLowStock())
            result.push_back(ingredient);
    }
    return result;
}

double SupplyManager::calculateOrderCost(const std::map<std::string, double>& order) const {
    double totalCost = 0.0;
    for (const auto& item : order) {
        for (const auto& ingredient : ingredients) {
            if (ingredient.getName() == item.first) {
                totalCost += ingredient.calculateCost(item.second);
                break;
            }
        }
    }
    return totalCost;
}

std::vector<std::string> SupplyManager::getSupplierNames() const {
    std::vector<std::string> names;
    for (const auto& supplier : suppliers) {
        names.push_back(supplier.getName());
    }
    return names;
}