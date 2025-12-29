#pragma once
#include "ProductBase.h"
#include <string>
#include <vector>
class Cake : public ProductBase {
private:
    double weight;
    std::string frostingType;
    int layers;
    std::vector<std::string> decorations;
    bool isGlutenFree;
public:
    Cake(const std::string& name, const std::string& code,
        double price, int quantity, double weight,
        const std::string& frosting, int layers = 1,
        bool glutenFree = false, double cost = 0.0);
    std::string getType() const override;
    std::string getDescription() const override;
    std::shared_ptr<ProductBase> clone() const override;
    double getWeight() const;
    std::string getFrostingType() const;
    int getLayers() const;
    bool isGlutenFreeCake() const;
    void addDecoration(const std::string& decoration);
    std::vector<std::string> getDecorations() const;
    double getPricePerKg() const;
    bool isMultiLayer() const;
};