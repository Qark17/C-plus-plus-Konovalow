#pragma once
#include <iostream>
#include <memory>
#include <initializer_list>
#include "Generator.h"
using namespace std;

class Array
{
private:
    size_t size;
    unique_ptr<int[]> data;
public:
    Array();
    Array(size_t size);
    Array(initializer_list<int> List);
    Array(const Array& other);
    ~Array();

    size_t getSize() const;
    bool checkEmpty() const;
    bool replacement();
    bool pop();
    bool newArray();
    
    void fill(Generator& generator);
    void randomArray(int min, int max);
    void cinArray(int size);
    void coutArray() const;
    void clear();
    Array& operator=(const Array& other);
    Array& operator<<(int shift);
    Array& operator>>(int shift);
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
};