#include "Candy.h"
Candy::Candy(const std::string& name, const std::string& code,
    double price, int quantity, const std::string& flavor,
    bool wrapper, bool sugarFree, const std::string& texture, double cost)
    : ProductBase(name, code, price, quantity, cost),
    flavor(flavor), hasWrapper(wrapper),
    isSugarFree(sugarFree), texture(texture) {
}
std::string Candy::getType() const {
    return "Candy";
}
std::string Candy::getDescription() const {
    std::string desc = ProductBase::getDescription() +
        ", Type: Candy, Flavor: " + flavor +
        ", Texture: " + texture +
        ", Wrapper: " + (hasWrapper ? "Yes" : "No") +
        ", Sugar-free: " + (isSugarFree ? "Yes" : "No");
    if (productionCost > 0)
        desc += ", Margin: " + std::to_string(getProfitMargin()) + "%";
    return desc;
}
std::shared_ptr<ProductBase> Candy::clone() const {
    return std::make_shared<Candy>(*this);
}
std::string Candy::getFlavor() const { return flavor; }
bool Candy::hasWrapperCandy() const { return hasWrapper; }
bool Candy::isSugarFreeCandy() const { return isSugarFree; }
std::string Candy::getTexture() const { return texture; }
void Candy::setFlavor(const std::string& newFlavor) {
    flavor = newFlavor;
}