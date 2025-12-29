#pragma once// ПОСТАВЩИКИ СЫРЬЯ
#include <string>
#include <vector>
#include <memory>
class Supplier {
private:
    std::string name;
    std::string contactInfo;
    std::string address;
    std::string contactPerson;
    std::vector<std::string> providedIngredients;
    double reliabilityRating;
public:
    Supplier(const std::string& name, const std::string& contact,
        const std::string& address = "", const std::string& person = "");
    void addIngredient(const std::string& ingredient);
    bool providesIngredient(const std::string& ingredient) const;
    std::string getName() const;
    std::string getContactInfo() const;
    std::string getAddress() const;
    std::string getContactPerson() const;
    std::vector<std::string> getProvidedIngredients() const;
    double getReliabilityRating() const;
    void setReliabilityRating(double rating);
    void setContactPerson(const std::string& person);
    std::string getFullInfo() const;
};