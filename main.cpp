#include <iostream>
#include <memory>
#include "Array.h"
#include "Generator.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
using namespace std;
// Ввод данных
int getValueInt(string message);
size_t getValue(string message);
enum FillMethod
{   manual = 1,    // Ручной ввод с клавиатуры
    random = 2,    // Случайные числа в заданном диапазоне
    constant = 3   // Постоянное значение для всех элементов
};
/**
*@brief Точка входа в программу
*@return точка выхода из программы
*/
int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    cout << "Введите размер массива: ";
    size_t size = getValue("");
    unique_ptr<Generator> generator;
    cout << "Как заполнить массив? Вручную - введите " << FillMethod::manual <<
        ", рандомом - " << FillMethod::random << ", константами - " << FillMethod::constant;
    int choice = getValueInt("");
    switch ((enum FillMethod)choice)
    {
    case FillMethod::manual:
        generator = make_unique<IStreamGenerator>(cin);
        cout << "Введите " << size << " чисел:\n";
        break;
    case FillMethod::random:
        generator = make_unique<RandomGenerator>(-10, 20);
        break;
    case FillMethod::constant:
        int value = getValueInt("Введите константное значение: ");
        generator = make_unique<ConstGenerator>(value);
        break;
    default:
        cerr << "Неверный выбор\n";
        return 1;
}
    Task1<int> task1(size, *generator);
    Task2<int> task2(size, *generator);
    Task3<int> task3(size, *generator);
    cout << "\n=== Исходный массив ===\n";
    cout << task1.getArray() << endl;
    cout << "\n=== Задание 1 ===\n";
    cout << task1.getDescription() << endl;
    cout << "Результат: " << task1.execute() << endl;
    cout << "\n=== Задание 2 ===\n";
    cout << task2.getDescription() << endl;
    cout << "Результат: " << task2.execute() << endl;
    cout << "\n=== Задание 3 ===\n";
    cout << task3.getDescription() << endl;
    cout << "Результат: " << task3.execute() << endl;
    return 0;
}
int getValueInt(string message)
{
    cout << message << endl;
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода!" << endl;
        exit(1);
    }
    return value;
}
size_t getValue(string message)
{
    cout << message << endl;
    int value = 0;
    cin >> value;
    if (cin.fail() || value < 0)
    {
        cout << "Длина минимум нулевая!" << endl;
        exit(1);
    }
    return value;
}