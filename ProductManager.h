#pragma once// УПРАВЛЕНИЕ всеми продуктами
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "ProductBase.h"
class ProductManager {
private:
    std::vector<std::unique_ptr<ProductBase>> products;
    std::map<std::string, int> salesCounter;
public:
    ProductManager() = default;
    /// @brief Добавляет продукт в менеджер
    /// @param product Умный указатель на продукт
    void addProduct(std::unique_ptr<ProductBase> product);
    /// @brief Удаляет продукт по коду
    /// @param productCode Код продукта для удаления
    void removeProduct(const std::string& productCode);
    /// @brief Находит продукт по коду
    /// @param productCode Код продукта
    /// @return Указатель на продукт или nullptr если не найден
    ProductBase* findProductByCode(const std::string& productCode) const;
    /// @brief Находит продукт по названию
    /// @param name Название продукта
    /// @return Указатель на продукт или nullptr если не найден
    ProductBase* findProductByName(const std::string& name) const;
    /// @brief Возвращает все продукты
    /// @return Вектор указателей на все продукты
    std::vector<ProductBase*> getAllProducts() const;
    /// @brief Возвращает продукты определенного типа
    /// @param type Тип продукта
    /// @return Вектор указателей на продукты заданного типа
    std::vector<ProductBase*> getProductsByType(const std::string& type) const;
    /// @brief Возвращает продукты с достаточным количеством на складе
    /// @param minQuantity Минимальное требуемое количество
    /// @return Вектор указателей на доступные продукты
    std::vector<ProductBase*> getAvailableProducts(int minQuantity = 1) const;
    /// @brief Возвращает ассортимент товаров с ценами
    /// @return Вектор пар (название, цена)
    std::vector<std::pair<std::string, double>> getProductAssortment() const;
    /// @brief Возвращает самый популярный товар
    /// @return Указатель на самый популярный продукт или nullptr если нет продуктов
    ProductBase* getMostPopularProduct() const;
    /// @brief Регистрирует продажу товара
    /// @param productCode Код продукта
    /// @param quantity Количество проданных единиц
    void recordSale(const std::string& productCode, int quantity);
    /// @brief Возвращает количество продаж для продукта
    /// @param productCode Код продукта
    /// @return Количество проданных единиц
    int getSalesCount(const std::string& productCode) const;
    /// @brief Рассчитывает общую стоимость инвентаря
    /// @return Общая стоимость товаров на складе
    double getTotalInventoryValue() const;
    /// @brief Возвращает продукты с низким запасом
    /// @param threshold Пороговое значение для низкого запаса
    /// @return Вектор указателей на продукты с низким запасом
    std::vector<ProductBase*> getLowStockProducts(int threshold = 10) const;
    /// @brief Ищет продукты по ключевому слову
    /// @param keyword Ключевое слово для поиска
    /// @return Вектор указателей на найденные продукты
    std::vector<ProductBase*> searchProducts(const std::string& keyword) const;
};