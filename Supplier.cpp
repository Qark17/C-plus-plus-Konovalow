#include "Supplier.h"
#include <algorithm>

Supplier::Supplier(const std::string& name, const std::string& contact,
    const std::string& address, const std::string& person)
    : name(name), contactInfo(contact), address(address),
    contactPerson(person), reliabilityRating(5.0) {
}

void Supplier::addIngredient(const std::string& ingredient) {
    if (std::find(providedIngredients.begin(), providedIngredients.end(),
        ingredient) == providedIngredients.end()) {
        providedIngredients.push_back(ingredient);
    }
}

bool Supplier::providesIngredient(const std::string& ingredient) const {
    return std::find(providedIngredients.begin(), providedIngredients.end(),
        ingredient) != providedIngredients.end();
}

std::string Supplier::getName() const { return name; }
std::string Supplier::getContactInfo() const { return contactInfo; }
std::string Supplier::getAddress() const { return address; }
std::string Supplier::getContactPerson() const { return contactPerson; }
std::vector<std::string> Supplier::getProvidedIngredients() const {
    return providedIngredients;
}
double Supplier::getReliabilityRating() const { return reliabilityRating; }

void Supplier::setReliabilityRating(double rating) {
    if (rating >= 0 && rating <= 10) reliabilityRating = rating;
}

void Supplier::setContactPerson(const std::string& person) {
    contactPerson = person;
}

std::string Supplier::getFullInfo() const {
    std::string info = "Supplier: " + name +
        "\nContact: " + contactInfo +
        "\nAddress: " + address +
        "\nContact Person: " + contactPerson +
        "\nReliability: " + std::to_string(reliabilityRating) +
        "\nIngredients: ";

    for (size_t i = 0; i < providedIngredients.size(); ++i) {
        info += providedIngredients[i];
        if (i < providedIngredients.size() - 1) info += ", ";
    }

    return info;
}