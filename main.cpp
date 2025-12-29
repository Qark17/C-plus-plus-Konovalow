#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <map>
#include "ProductBase.h"
#include "Chocolate.h"
#include "Candy.h"
#include "Cake.h"
#include "ProductManager.h"
#include "SupplyManager.h"
#include "SalesManager.h"
#include "ReportGenerator.h"
// @brief Демонстрационная программа для кондитерской фабрики
// @brief Отображает все продукты из коллекции
void displayProducts(const std::vector<ProductBase*>& products) {
    std::cout << "\n=== КОЛЛЕКЦИЯ ПРОДУКТОВ ===\n";
    for (size_t i = 0; i < products.size(); ++i) {
        std::cout << i + 1 << ". " << products[i]->getDescription() << std::endl;
    }
}
std::map<std::string, std::shared_ptr<ProductBase>> createProductMap(
    const std::vector<std::unique_ptr<ProductBase>>& productCollection) {
    std::map<std::string, std::shared_ptr<ProductBase>> productMap;
    for (const auto& product : productCollection) {
        productMap[product->getProductCode()] = product->clone();
    }
    return productMap;
}
// @brief Анализирует коллекцию продуктов
void analyzeProductCollection(const std::vector<ProductBase*>& products) {
    std::cout << "\n=== АНАЛИЗ КОЛЛЕКЦИИ ===\n";

    int chocolateCount = 0, candyCount = 0, cakeCount = 0;
    double totalValue = 0.0;
    int totalQuantity = 0;

    for (const auto& product : products) {
        std::string type = product->getType();
        if (type == "Chocolate") chocolateCount++;
        else if (type == "Candy") candyCount++;
        else if (type == "Cake") cakeCount++;
        totalValue += product->getPrice() * product->getQuantity();
        totalQuantity += product->getQuantity();
    }
    std::cout << "Статистика по типам:\n";
    std::cout << "  Шоколад: " << chocolateCount << " видов\n";
    std::cout << "  Конфеты: " << candyCount << " видов\n";
    std::cout << "  Торты: " << cakeCount << " видов\n";
    std::cout << "  Всего: " << products.size() << " видов продуктов\n\n";
    std::cout << "Количественные показатели:\n";
    std::cout << "  Общее количество на складе: " << totalQuantity << " единиц\n";
    std::cout << "  Общая стоимость товара: " << totalValue << " руб.\n";

    if (!products.empty()) {
        ProductBase* mostExpensive = products[0];
        ProductBase* cheapest = products[0];
        for (const auto& product : products) {
            if (product->getPrice() > mostExpensive->getPrice())
                mostExpensive = product;
            if (product->getPrice() < cheapest->getPrice())
                cheapest = product;
        }
        std::cout << "\nЭкстремальные значения:\n";
        std::cout << "  Самый дорогой: " << mostExpensive->getName()
            << " (" << mostExpensive->getPrice() << " руб.)\n";
        std::cout << "  Самый дешевый: " << cheapest->getName()
            << " (" << cheapest->getPrice() << " руб.)\n";
    }
}
int main() {
    ProductManager productManager;
    SupplyManager supplyManager;
    SalesManager salesManager;
    std::cout << "1. СОЗДАНИЕ ПРОДУКТОВ...\n";
    std::vector<std::unique_ptr<ProductBase>> productCollection;
    productCollection.push_back(std::make_unique<Chocolate>(
        "Alpen Gold Молочный", "CHOCO001", 150.0, 1000, 35, false, "", 90.0));
    productCollection.push_back(std::make_unique<Chocolate>(
        "Babaevsky Elite", "CHOCO002", 200.0, 800, 72, true, "", 120.0));
    productCollection.push_back(std::make_unique<Chocolate>(
        "Ritter Sport с орехами", "CHOCO003", 180.0, 600, 50, false, "орехи", 110.0));
    productCollection.push_back(std::make_unique<Candy>(
        "Mentos Fruit", "CANDY001", 80.0, 5000, "фруктовый", true, false, "жевательная", 45.0));
    productCollection.push_back(std::make_unique<Candy>(
        "Chupa Chups", "CANDY002", 25.0, 10000, "карамель", true, false, "твердая", 12.0));
    productCollection.push_back(std::make_unique<Candy>(
        "Raffaello", "CANDY003", 350.0, 300, "кокос", false, false, "мягкая", 210.0));
    productCollection.push_back(std::make_unique<Cake>(
        "Наполеон", "CAKE001", 450.0, 50, 2.5, "заварной крем", 3, false, 280.0));
    productCollection.push_back(std::make_unique<Cake>(
        "Медовик", "CAKE002", 380.0, 40, 2.0, "медовый крем", 2, true, 230.0));
    productCollection.push_back(std::make_unique<Cake>(
        "Прага", "CAKE003", 520.0, 30, 3.0, "шоколадный крем", 4, false, 320.0));

    for (auto& product : productCollection) {
        productManager.addProduct(std::move(product));
    }
    std::cout << "\n2. ДЕМОНСТРАЦИЯ ПОЛИМОРФИЗМА:\n";
    auto allProducts = productManager.getAllProducts();
    displayProducts(allProducts);
    analyzeProductCollection(allProducts);
    std::cout << "\n3. СОЗДАНИЕ ПОСТАВЩИКОВ И ИНГРЕДИЕНТОВ...\n";
    Supplier sugarSupplier("Сахарный завод", "+7-495-111-2233", "Москва, ул. Сахарная, 1", "Иванов И.И.");
    Supplier cocoaSupplier("Какао Импорт", "+7-495-222-3344", "Москва, ул. Шоколадная, 15", "Петров П.П.");
    Supplier dairySupplier("Молочный комбинат", "+7-495-333-4455", "Москва, ул. Молочная, 7", "Сидоров С.С.");

    sugarSupplier.setReliabilityRating(8.5);
    cocoaSupplier.setReliabilityRating(9.0);
    dairySupplier.setReliabilityRating(7.5);

    supplyManager.addSupplier(sugarSupplier);
    supplyManager.addSupplier(cocoaSupplier);
    supplyManager.addSupplier(dairySupplier);

    supplyManager.addIngredient(Ingredient("Сахар", "кг", 50.0, "Сахарный завод", 100, 500));
    supplyManager.addIngredient(Ingredient("Какао-порошок", "кг", 200.0, "Какао Импорт", 50, 200));
    supplyManager.addIngredient(Ingredient("Какао-масло", "кг", 300.0, "Какао Импорт", 20, 100));
    supplyManager.addIngredient(Ingredient("Молоко", "л", 80.0, "Молочный комбинат", 200, 800));
    supplyManager.addIngredient(Ingredient("Сливки", "л", 120.0, "Молочный комбинат", 100, 400));
    supplyManager.addIngredient(Ingredient("Мука", "кг", 40.0, "Сахарный завод", 200, 1000));

    supplyManager.associateIngredientWithSupplier("Сахар", "Сахарный завод");
    supplyManager.associateIngredientWithSupplier("Какао-порошок", "Какао Импорт");
    supplyManager.associateIngredientWithSupplier("Какао-масло", "Какао Импорт");
    supplyManager.associateIngredientWithSupplier("Молоко", "Молочный комбинат");
    supplyManager.associateIngredientWithSupplier("Сливки", "Молочный комбинат");
    supplyManager.associateIngredientWithSupplier("Мука", "Сахарный завод");

    std::cout << "\n4. СОЗДАНИЕ МАГАЗИНОВ И ЗАКАЗОВ...\n";
    auto productMap = createProductMap(productCollection);
    Shop supermarket("Супермаркет 'Вкусный'", "Москва, ул. Центральная, 10", "+7-495-444-5566", "Смирнова А.А.");
    supermarket.setRegularCustomer(true);
    supermarket.setDiscount(10.0);

    Shop minimarket("Минимаркет 'Сладости'", "Москва, ул. Сладкая, 5", "+7-495-555-6677", "Кузнецова Е.В.");
    minimarket.setRegularCustomer(true);
    minimarket.setDiscount(5.0);

    Shop convenienceStore("Магазин 'У дома'", "Москва, ул. Домашняя, 3", "+7-495-666-7788", "Попов Д.С.");
    salesManager.addShop(supermarket);
    salesManager.addShop(minimarket);
    salesManager.addShop(convenienceStore);

    std::time_t now = std::time(nullptr);
    std::time_t tomorrow = now + 24 * 60 * 60;
    std::time_t nextWeek = now + 7 * 24 * 60 * 60;

    Order order1("Супермаркет 'Вкусный'", productMap["CHOCO001"], 100, 150.0);
    Order order2("Супермаркет 'Вкусный'", productMap["CANDY001"], 500, 80.0);
    Order order3("Минимаркет 'Сладости'", productMap["CHOCO002"], 50, 200.0);
    Order order4("Минимаркет 'Сладости'", productMap["CAKE001"], 10, 450.0);
    Order order5("Магазин 'У дома'", productMap["CANDY002"], 1000, 25.0);

    order1.setStatus("processing");
    order2.setStatus("shipped");
    order3.setStatus("delivered");
    order3.setDeliveryDate(now - 2 * 24 * 60 * 60);
    order4.setStatus("pending");
    order5.setStatus("processing");

    supermarket.placeOrder(order1);
    supermarket.placeOrder(order2);
    minimarket.placeOrder(order3);
    minimarket.placeOrder(order4);
    convenienceStore.placeOrder(order5);

    salesManager.addOrder(order1);
    salesManager.addOrder(order2);
    salesManager.addOrder(order3);
    salesManager.addOrder(order4);
    salesManager.addOrder(order5);

    SaleRecord sale1("CHOCO001", 50, 7500.0, "Супермаркет 'Вкусный'");
    SaleRecord sale2("CANDY001", 200, 16000.0, "Минимаркет 'Сладости'");
    SaleRecord sale3("CAKE001", 5, 2250.0, "Магазин 'У дома'");
    SaleRecord sale4("CHOCO002", 30, 6000.0, "Супермаркет 'Вкусный'");
    SaleRecord sale5("CANDY002", 500, 12500.0, "Минимаркет 'Сладости'");

    salesManager.addSale(sale1);
    salesManager.addSale(sale2);
    salesManager.addSale(sale3);
    salesManager.addSale(sale4);
    salesManager.addSale(sale5);

    productManager.recordSale("CHOCO001", 50);
    productManager.recordSale("CANDY001", 200);
    productManager.recordSale("CAKE001", 5);
    productManager.recordSale("CHOCO002", 30);
    productManager.recordSale("CANDY002", 500);
    std::cout << "\n--- Список магазинов, заказывающих товар 'CHOCO001' ---\n";
    auto shopsWithProduct = salesManager.getShopsByProduct("CHOCO001");
    for (const auto& shop : shopsWithProduct) {
        std::cout << "- " << shop.getName() << " (" << shop.getAddress() << ")\n";
    }
    std::cout << "\n--- Список ингредиентов от поставщика 'Какао Импорт' ---\n";
    auto ingredientsFromSupplier = supplyManager.getIngredientsBySupplier("Какао Импорт");
    for (const auto& ingredient : ingredientsFromSupplier) {
        std::cout << "- " << ingredient.getName() << " (" << ingredient.getPricePerUnit()
            << " руб./" << ingredient.getUnit() << ")\n";
    }
    std::cout << "\n--- Ассортимент товара и цены ---\n";
    auto assortment = productManager.getProductAssortment();
    for (const auto& item : assortment) {
        std::cout << "- " << item.first << ": " << item.second << " руб.\n";
    }
    std::cout << "\n--- Самый популярный товар ---\n";
    auto mostPopular = productManager.getMostPopularProduct();
    if (mostPopular) {
        std::cout << "Самый популярный товар: " << mostPopular->getName()
            << " (продано: " << productManager.getSalesCount(mostPopular->getProductCode())
            << " единиц)\n";
    }
    std::cout << "\n--- Стоимость произведенного товара ---\n";
    std::time_t weekAgo = now - 7 * 24 * 60 * 60;
    auto recentOrders = salesManager.getOrdersByPeriod(weekAgo, now);
    double productionCost = ReportGenerator::calculateProductionCost(recentOrders, allProducts);
    std::cout << "Стоимость произведенного товара за последнюю неделю: "
        << productionCost << " руб.\n";

    std::cout << "\n6. ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ СИСТЕМЫ:\n";
    std::cout << "\n--- Отчет по инвентарю ---\n";
    std::cout << ReportGenerator::generateInventoryReport(allProducts) << std::endl;
    std::cout << "\n--- Отчет по продажам за неделю ---\n";
    auto weeklySales = salesManager.getSalesByPeriod(weekAgo, now);
    std::cout << ReportGenerator::generateSalesReport(weeklySales, weekAgo, now) << std::endl;
    std::cout << "\n--- Отчет по продуктам ---\n";
    std::cout << ReportGenerator::generateProductPerformanceReport(allProducts, weeklySales) << std::endl;
    std::cout << "\n--- Поиск товаров по ключевому слову 'шоколад' ---\n";
    auto searchResults = productManager.searchProducts("шоколад");
    if (!searchResults.empty()) {
        for (const auto& product : searchResults) {
            std::cout << "- " << product->getName() << " (" << product->getType() << ")\n";
        }
    }
    else {
        std::cout << "Товары не найдены.\n";
    }
    std::cout << "\n--- Продукты с низким запасом (< 100 единиц) ---\n";
    auto lowStockProducts = productManager.getLowStockProducts(100);
    if (!lowStockProducts.empty()) {
        for (const auto& product : lowStockProducts) {
            std::cout << "- " << product->getName() << " (остаток: " << product->getQuantity() << ")\n";
        }
    }
    else {
        std::cout << "Нет продуктов с низким запасом.\n";
    }
    std::cout << "\n7. ИТОГИ РАБОТЫ СИСТЕМЫ:\n";
    std::cout << "• Управление продуктами: " << productManager.getAllProducts().size() << " товаров\n";
    std::cout << "• Управление поставщиками: " << supplyManager.getSupplierNames().size() << " поставщиков\n";
    std::cout << "• Управление продажами: " << salesManager.getShopNames().size() << " магазинов-партнеров\n";
    std::cout << "• Обработано заказов: " << recentOrders.size() << " за последнюю неделю\n";
    std::cout << "• Общая стоимость инвентаря: " << productManager.getTotalInventoryValue() << " руб.\n";
    return 0;
}