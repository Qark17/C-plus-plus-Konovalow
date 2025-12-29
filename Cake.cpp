#include "Cake.h"
#include <algorithm>
Cake::Cake(const std::string& name, const std::string& code,
    double price, int quantity, double weight,
    const std::string& frosting, int layers, bool glutenFree, double cost)
    : ProductBase(name, code, price, quantity, cost),
    weight(weight), frostingType(frosting),
    layers(layers), isGlutenFree(glutenFree)
{
    if (weight <= 0) weight = 0.5;
    if (layers <= 0) layers = 1;
}
std::string Cake::getType() const {
    return "Cake";
}
std::string Cake::getDescription() const {
    std::string desc = ProductBase::getDescription() +
        ", Type: Cake, Weight: " + std::to_string(weight) +
        " kg, Frosting: " + frostingType +
        ", Layers: " + std::to_string(layers) +
        ", Gluten-free: " + (isGlutenFree ? "Yes" : "No");
    if (!decorations.empty()) {
        desc += ", Decorations: ";
        for (size_t i = 0; i < decorations.size(); ++i) {
            desc += decorations[i];
            if (i < decorations.size() - 1) desc += ", ";
        }
    }
    if (productionCost > 0) {
        desc += ", Margin: " + std::to_string(getProfitMargin()) + "%";
        desc += ", Price/kg: " + std::to_string(getPricePerKg());
    }
    return desc;
}
std::shared_ptr<ProductBase> Cake::clone() const {
    return std::make_shared<Cake>(*this);
}
double Cake::getWeight() const { return weight; }
std::string Cake::getFrostingType() const { return frostingType; }
int Cake::getLayers() const { return layers; }
bool Cake::isGlutenFreeCake() const { return isGlutenFree; }
void Cake::addDecoration(const std::string& decoration) {
    decorations.push_back(decoration);
}
std::vector<std::string> Cake::getDecorations() const {
    return decorations;
}
double Cake::getPricePerKg() const {
    if (weight > 0) return price / weight;
    return 0.0;
}
bool Cake::isMultiLayer() const {
    return layers > 1;
}