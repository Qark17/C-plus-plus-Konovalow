#pragma once
#include <iostream>
#include <random>
using namespace std;
class Generator
{
private:
    enum class Mode {Random, Cin};
    Mode mode;
    istream* input;
    int min, max;
    mt19937 random_gen;
    uniform_int_distribution<int> distribution;
public:
    Generator(int min, int max): mode(Mode::Random), input(nullptr), min(min), max(max),
        random_gen(mt19937(random_device{}())), distribution(uniform_int_distribution<int>(min, max)) {    }
    Generator(istream& input = cin): mode(Mode::Cin), input(&input), min(0), max(0),
        random_gen(mt19937(random_device{}())), distribution(uniform_int_distribution<int>(0, 0)) {    }
    int generate()
    {
        switch (mode)
        {
        case Mode::Random:
            return distribution(random_gen);
        case Mode::Cin:
            int value;
            *input >> value;
            return value;
        }
    }
};