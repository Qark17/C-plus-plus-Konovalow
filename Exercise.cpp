#include "Exercise.h"
#include "Generator.h"
template<typename T>
Exercise<T>::Exercise(size_t size, Generator& generator) : array(size) {
array.fillFromGenerator(generator);
}
template class Exercise<int>;