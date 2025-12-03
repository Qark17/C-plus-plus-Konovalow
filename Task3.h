#pragma once
#include "Exercise.h"


    template<typename T>
    class Task3 : public Exercise<T> {
    public:
        Task3(size_t size, Generator& generator);
        Array<T> execute() const override;
        std::string getDescription() const override;
    };
