#pragma once// управление ЦЕПОЧКОЙ поставок СЫРЬЯ
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Supplier.h"
#include "Ingredient.h"
class SupplyManager {
private:
    std::vector<Supplier> suppliers;
    std::vector<Ingredient> ingredients;
    std::map<std::string, std::vector<std::string>> supplierToIngredients;
    std::map<std::string, std::vector<std::string>> ingredientToSuppliers;
public:
    void addSupplier(const Supplier& supplier);
    void addIngredient(const Ingredient& ingredient);
    /// @brief Связывает ингредиент с поставщиком
    void associateIngredientWithSupplier(const std::string& ingredientName,
        const std::string& supplierName);
    std::vector<Ingredient> getIngredientsBySupplier(const std::string& supplierName) const;
    Supplier* findSupplierByName(const std::string& name);
    Ingredient* findIngredientByName(const std::string& name);
    std::vector<Supplier> getSuppliersByIngredient(const std::string& ingredientName) const;
    std::vector<Supplier> getReliableSuppliers(double minRating = 7.0) const;
    std::vector<Ingredient> getLowStockIngredients() const;
    double calculateOrderCost(const std::map<std::string, double>& order) const;
    std::vector<std::string> getSupplierNames() const;
};