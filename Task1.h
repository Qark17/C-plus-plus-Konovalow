#pragma once
#include "Exercise.h"

    template<typename T>
    class Task1 : public Exercise<T> {
    public:
        Task1(size_t size, Generator& generator);
        Array<T> execute() const override;
        std::string getDescription() const override;
    };
