#include "Chocolate.h"

Chocolate::Chocolate(const std::string& name, const std::string& code,
    double price, int quantity, int cocoaPercent,
    bool dark, const std::string& filling, double cost)
    : ProductBase(name, code, price, quantity, cost),
    cocoaPercentage(cocoaPercent), isDark(dark), filling(filling)
{
    if (cocoaPercentage < 0) cocoaPercentage = 0;
    if (cocoaPercentage > 100) cocoaPercentage = 100;
}

std::string Chocolate::getType() const {
    return "Chocolate";
}

std::string Chocolate::getDescription() const {
    std::string desc = ProductBase::getDescription() +
        ", Type: Chocolate, Cocoa: " + std::to_string(cocoaPercentage) + "%";

    desc += isDark ? ", Dark" : ", Milk";

    if (!filling.empty())
        desc += ", Filling: " + filling;

    if (productionCost > 0)
        desc += ", Margin: " + std::to_string(getProfitMargin()) + "%";

    return desc;
}

int Chocolate::getCocoaPercentage() const {
    return cocoaPercentage;
}

bool Chocolate::isDarkChocolate() const {
    return isDark;
}

std::string Chocolate::getFilling() const {
    return filling;
}

void Chocolate::setFilling(const std::string& newFilling) {
    filling = newFilling;
}

bool Chocolate::isBitter() const {
    return cocoaPercentage >= 70;
}