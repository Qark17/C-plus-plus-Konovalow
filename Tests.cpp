#include <memory>
#include <vector>
#include "Chocolate.h"
#include "Candy.h"
#include "Cake.h"
#include "ProductManager.h"
#include "Supplier.h"
#include "Ingredient.h"
#include "Shop.h"
#include "Order.h"
TEST(ChocolateTest, ConstructorAndGetters) {
    Chocolate choco("Test Chocolate", "TEST001", 100.0, 50, 70, true, "орехи", 60.0);

    EXPECT_EQ(choco.getName(), "Test Chocolate");
    EXPECT_EQ(choco.getType(), "Chocolate");
    EXPECT_EQ(choco.getProductCode(), "TEST001");
    EXPECT_EQ(choco.getPrice(), 100.0);
    EXPECT_EQ(choco.getQuantity(), 50);
    EXPECT_EQ(choco.getCocoaPercentage(), 70);
    EXPECT_TRUE(choco.isDarkChocolate());
    EXPECT_EQ(choco.getFilling(), "орехи");
    EXPECT_EQ(choco.getProductionCost(), 60.0);
    EXPECT_GT(choco.getProfitMargin(), 0);
}

TEST(ChocolateTest, IsBitter) {
    Chocolate bitter("Bitter", "B001", 100.0, 10, 75, true);
    Chocolate milk("Milk", "M001", 100.0, 10, 35, false);

    EXPECT_TRUE(bitter.isBitter());
    EXPECT_FALSE(milk.isBitter());
}

// Тесты для Candy
TEST(CandyTest, ConstructorAndGetters) {
    Candy candy("Test Candy", "CANDYTEST", 50.0, 100, "фруктовый", true, false, "жевательная", 30.0);

    EXPECT_EQ(candy.getName(), "Test Candy");
    EXPECT_EQ(candy.getType(), "Candy");
    EXPECT_EQ(candy.getFlavor(), "фруктовый");
    EXPECT_TRUE(candy.hasWrapperCandy());
    EXPECT_FALSE(candy.isSugarFreeCandy());
    EXPECT_EQ(candy.getTexture(), "жевательная");
}

// Тесты для Cake
TEST(CakeTest, ConstructorAndGetters) {
    Cake cake("Test Cake", "CAKETEST", 200.0, 20, 2.0, "крем", 3, false, 120.0);

    EXPECT_EQ(cake.getName(), "Test Cake");
    EXPECT_EQ(cake.getType(), "Cake");
    EXPECT_EQ(cake.getWeight(), 2.0);
    EXPECT_EQ(cake.getFrostingType(), "крем");
    EXPECT_EQ(cake.getLayers(), 3);
    EXPECT_FALSE(cake.isGlutenFreeCake());
    EXPECT_GT(cake.getPricePerKg(), 0);
}

TEST(CakeTest, Decorations) {
    Cake cake("Decorated", "DECO", 300.0, 10, 2.5, "крем");

    cake.addDecoration("ягоды");
    cake.addDecoration("шоколад");

    auto decorations = cake.getDecorations();
    EXPECT_EQ(decorations.size(), 2);
    EXPECT_EQ(decorations[0], "ягоды");
    EXPECT_EQ(decorations[1], "шоколад");
}

// Тесты для ProductManager
TEST(ProductManagerTest, AddAndFindProduct) {
    ProductManager manager;

    auto chocolate = std::make_unique<Chocolate>("Test", "T001", 100.0, 10, 50, true);
    manager.addProduct(std::move(chocolate));

    auto found = manager.findProductByCode("T001");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getName(), "Test");

    auto notFound = manager.findProductByCode("NONEXISTENT");
    EXPECT_EQ(notFound, nullptr);
}

TEST(ProductManagerTest, RemoveProduct) {
    ProductManager manager;

    manager.addProduct(std::make_unique<Chocolate>("Test1", "T001", 100.0, 10, 50, true));
    manager.addProduct(std::make_unique<Candy>("Test2", "T002", 50.0, 20, "фрукт", true));

    EXPECT_NE(manager.findProductByCode("T001"), nullptr);

    manager.removeProduct("T001");
    EXPECT_EQ(manager.findProductByCode("T001"), nullptr);
    EXPECT_NE(manager.findProductByCode("T002"), nullptr);
}

TEST(ProductManagerTest, GetProductsByType) {
    ProductManager manager;

    manager.addProduct(std::make_unique<Chocolate>("Choco1", "C1", 100.0, 10, 50, true));
    manager.addProduct(std::make_unique<Chocolate>("Choco2", "C2", 120.0, 15, 60, true));
    manager.addProduct(std::make_unique<Candy>("Candy1", "CD1", 50.0, 20, "фрукт", true));

    auto chocolates = manager.getProductsByType("Chocolate");
    EXPECT_EQ(chocolates.size(), 2);

    auto candies = manager.getProductsByType("Candy");
    EXPECT_EQ(candies.size(), 1);

    auto cakes = manager.getProductsByType("Cake");
    EXPECT_EQ(cakes.size(), 0);
}

TEST(ProductManagerTest, RecordSaleAndMostPopular) {
    ProductManager manager;

    manager.addProduct(std::make_unique<Chocolate>("Choco1", "C1", 100.0, 100, 50, true));
    manager.addProduct(std::make_unique<Candy>("Candy1", "CD1", 50.0, 200, "фрукт", true));

    // Записываем продажи
    manager.recordSale("C1", 30);
    manager.recordSale("CD1", 50);
    manager.recordSale("C1", 20);  // Еще продажи шоколада

    EXPECT_EQ(manager.getSalesCount("C1"), 50);
    EXPECT_EQ(manager.getSalesCount("CD1"), 50);

    // При равных продажах должен вернуть первый добавленный
    auto popular = manager.getMostPopularProduct();
    EXPECT_NE(popular, nullptr);
}

// Тесты для Supplier
TEST(SupplierTest, ConstructorAndMethods) {
    Supplier supplier("Test Supplier", "+7-999-123-4567", "Test Address", "Test Person");

    EXPECT_EQ(supplier.getName(), "Test Supplier");
    EXPECT_EQ(supplier.getContactInfo(), "+7-999-123-4567");
    EXPECT_EQ(supplier.getAddress(), "Test Address");
    EXPECT_EQ(supplier.getContactPerson(), "Test Person");
    EXPECT_EQ(supplier.getReliabilityRating(), 5.0);

    supplier.addIngredient("Сахар");
    supplier.addIngredient("Мука");

    auto ingredients = supplier.getProvidedIngredients();
    EXPECT_EQ(ingredients.size(), 2);
    EXPECT_TRUE(supplier.providesIngredient("Сахар"));
    EXPECT_FALSE(supplier.providesIngredient("Молоко"));
}

// Тесты для Ingredient
TEST(IngredientTest, ConstructorAndMethods) {
    Ingredient ingredient("Сахар", "кг", 50.0, "Поставщик", 100, 500);

    EXPECT_EQ(ingredient.getName(), "Сахар");
    EXPECT_EQ(ingredient.getUnit(), "кг");
    EXPECT_EQ(ingredient.getPricePerUnit(), 50.0);
    EXPECT_EQ(ingredient.getSupplierName(), "Поставщик");
    EXPECT_EQ(ingredient.getMinOrderQuantity(), 100);
    EXPECT_EQ(ingredient.getStockQuantity(), 500);

    EXPECT_EQ(ingredient.calculateCost(10), 500.0);
    EXPECT_TRUE(ingredient.canOrder(150));
    EXPECT_FALSE(ingredient.canOrder(50));
    EXPECT_FALSE(ingredient.isLowStock());

    ingredient.updateStock(-450);
    EXPECT_TRUE(ingredient.isLowStock());
}

// Тесты для Shop
TEST(ShopTest, ConstructorAndOrders) {
    Shop shop("Test Shop", "Test Address", "+7-999-111-2233", "Test Manager");

    shop.placeOrder("PROD001", 10);
    shop.placeOrder("PROD002", 5);
    shop.placeOrder("PROD001", 5);  // Дополнительный заказ того же товара

    auto orders = shop.getOrders();
    EXPECT_EQ(orders.size(), 2);  // Два уникальных товара
    EXPECT_EQ(shop.getTotalOrderedQuantity(), 20);  // 10+5+5

    shop.cancelOrder("PROD001");
    orders = shop.getOrders();
    EXPECT_EQ(orders.size(), 1);
    EXPECT_EQ(orders[0].first, "PROD002");
}

TEST(ShopTest, DiscountCalculation) {
    Shop shop("Test Shop", "Address");

    shop.setRegularCustomer(true);
    shop.setDiscount(10.0);

    // 100 руб. * 10 единиц = 1000 руб., минус 10% = 900 руб.
    double total = shop.calculateOrderTotal(100.0, 10);
    EXPECT_DOUBLE_EQ(total, 900.0);
}

// Тесты для Order
TEST(OrderTest, ConstructorAndMethods) {
    Order order("Test Shop", "PROD001", 10, 100.0);

    EXPECT_GE(order.getOrderId(), 1000);
    EXPECT_EQ(order.getShopName(), "Test Shop");
    EXPECT_EQ(order.getProductCode(), "PROD001");
    EXPECT_EQ(order.getQuantity(), 10);
    EXPECT_EQ(order.getTotalPrice(), 1000.0);
    EXPECT_EQ(order.getStatus(), "pending");
    EXPECT_FALSE(order.isPaidOrder());
    EXPECT_FALSE(order.isDelivered());

    order.markAsPaid();
    EXPECT_TRUE(order.isPaidOrder());

    order.setStatus("delivered");
    EXPECT_TRUE(order.isDelivered());
}

// Основная функция для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}