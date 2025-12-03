#pragma once
#include "Exercise.h"
#include <vector>


    template<typename T>
    class Task2 : public Exercise<T> {
    public:
        Task2(size_t size, Generator& generator);
        Array<T> execute() const override;
        std::string getDescription() const override;

    private:
        bool hasSameFirstTwoDigits(T number) const;
    };
