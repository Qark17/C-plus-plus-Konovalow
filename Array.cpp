#include "Array.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
//#include <ctime>
using namespace std;

Array::Array()
{
    size = 0;
    data = nullptr;
}
Array::Array(size_t size) : size(size), data(make_unique<int[]>(size))
{
    for (size_t i = 0; i < size; ++i)
        data[i] = 0;
}
Array::Array(initializer_list<int> List)
{
    size = List.size();
    data = make_unique<int[]>(size);
    for (size_t i = 0; int elmnt : List)
        data[i++] = elmnt;
}
Array::Array(const Array& other): size(other.size), data(make_unique<int[]>(other.size))
{
    for (size_t i = 0; i < size; ++i)
        data[i] = other.data[i];
}
Array::~Array() = default;

size_t Array::getSize() const
{
    return size;
}
bool Array::checkEmpty() const
{
    return size == 0;
}
bool Array::replacement()
{
    if (checkEmpty())
        return false;
    for (size_t i = size - 1; i >= 0; --i)
    {
        if (data[i] < 0)
        {
            data[i] = abs(data[0]);
            return true;
        }
    }
    return false;
}
bool Array::pop()
{
    if (checkEmpty())
        return false;
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = abs(data[i]);
        if (data[i] < 10)
            return false;
        while (data[i] >= 100)
            data[i] /= 10;
        int first = data[i] / 10;
        int second = data[i] % 10;
        if (first == second)
        {
            size_t newSize = size - 1;
            auto newData = make_unique<int[]>(newSize);
            for (size_t i = 0; i < newSize; ++i)
                newData[i] = data[i];
        data = move(newData);
        size = newSize;
        return true;
        }
    }
    return true;
}
bool Array::newArray()
{
    if (checkEmpty())
        return false;
    for (size_t i = 0; i < size; ++i)
    {
        if (i % 2 == 0)
            data[i] = i * data[i];
        else
            (data[i] = -data[i]);
        size_t newSize = size - 1;
        auto newData = make_unique<int[]>(newSize);
        for (size_t i = 0; i < newSize; ++i)
            newData[i] = data[i];
        data = move(newData);
        size = newSize;
    }
    return true;
}

void Array::fill(Generator& generator)
{
    for (size_t i = 0; i < size; ++i)
        data[i] = generator.generate();
}
void Array::randomArray(int min, int max)
{
    for (size_t i = 0; i < size; ++i)
        data[i] = rand() % (max - min + 1) + min;
}
void Array::cinArray(int size)
{
    data = make_unique<int[]>(size);
    cout << "Введите " << size << " элементов:\n";
    for (size_t i = 0; i < size; ++i)
    {
        cout << "Введите " << i+1 << "-й элемент: ";
        cin >> data[i];
    }
}
void Array::coutArray() const
{
    if (!Array::checkEmpty())
    {
        //cout << "(пустой массив)\n";
        //return;
        cout << "Массив: [";
        for (size_t i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << "]" << endl;
    }
}
void Array::clear()
{
    size = 0;
    data = nullptr;
}

Array& Array::operator=(const Array& other)
{
    if (this == &other)
        return *this;
    size = other.size;
    data = make_unique<int[]>(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = other.data[i];
    return *this;
}
Array& Array::operator<<(int shift)
{
    if (size == 0)
        return *this;
    shift = shift % size;
    if (shift == 0)
        return *this;
    auto temp = make_unique<int[]>(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = data[(i + shift) % size];
    data = move(temp);
    return *this;
}
Array& Array::operator>>(int shift)
{
    if (size == 0)
        return *this;
    shift = shift % size;
    if (shift == 0)
        return *this;
    auto temp = make_unique<int[]>(size);
    for (size_t i = 0; i < size; ++i)
        data[i] = data[(i + size - shift) % size];
    data = move(temp);
    return *this;
}
int& Array::operator[](size_t index)
{
    return data[index];
}
const int& Array::operator[](size_t index) const
{
    return data[index];
}