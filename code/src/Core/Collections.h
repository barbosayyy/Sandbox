#pragma once

#include "vector"

namespace SbEngine{
    template<typename T>
    struct SparseSet{
    public:
        void Insert(size_t element, T data);
        void Remove(size_t element);
        T Get(size_t element);
        void Clear();
    private:
        std::vector<T> _dense;
        std::vector<size_t> _sparse;
    };
}