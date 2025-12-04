#include "ConstGenerator.h"
ConstGenerator::ConstGenerator(const int value) : value(value) {}
int ConstGenerator::generate()
{
    return value;
}