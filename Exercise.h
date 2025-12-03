#pragma once
#include "Array.h"
#include <memory>
#include <string>


    template<typename T>
    class Exercise {
    protected:
        Array<T> array;

    public:
        Exercise(size_t size, Generator& generator);
        virtual ~Exercise() = default;

        const Array<T>& getArray() const { return array; }
        virtual Array<T> execute() const = 0;
        virtual std::string getDescription() const = 0;
    };
