#pragma once

#include "Core/Debug.h"
#include <algorithm>
#include <vector>

namespace Sb {
    template<typename T>
    struct SparseSet{
    public:

        void Insert(u32 element, T data) {
            if(Contains(element)) {
                Sb::Log::Warn("Collections; Sparse Set: Sparse already points to value in dense set");
                return;
            }

            if(element >= _sparse.size()) {
                u32 new_size = std::max<u32>(element+1, _sparse.size() * _RESIZE_FACTOR);
                _sparse.resize(new_size, _MAX_U32);
            }

            _sparse[element] = _dense.size();
            _dense.emplace_back(data);
            _dense.back().sparseIndex = element;
        }

        void Remove(u32 element) {
            // Log::Warn("Collections: SparseSet.Remove(u32 element) is not implemented!");
            if(Contains(element)) {
                u32 denseId = _sparse[element];
                _dense[denseId] = _dense.back();
                _sparse[_dense.back().sparseIndex] = denseId;
                _dense.pop_back();
                _sparse[element] = _MAX_U32;
#ifdef SB_BUILD_DEBUG
                Log::Info(typeid(T).name(), " SparseSet Removed element ", element);
#endif
            }
        }
        
        T& Get(u32 element) {
            assert(Contains(element) && "Collections: Element not found in SparseSet");
            return _dense[_sparse[element]];
        }

        bool Contains(u32 element) const {
            return element < _sparse.size() && _sparse[element] != _MAX_U32;
        }

        void Clear() {
            _dense.clear();
            _sparse.clear();
        }

        std::vector<T>& GetDense() { return _dense; };
        std::vector<u32>& GetSparse() { return _sparse; };
        
#ifdef SB_BUILD_DEBUG
        void PrintSparse() { for(int i = 0; i < _sparse.size(); i++) { Log::Print(typeid(T).name(), " Sparse at ", i, " = ", _sparse.at(i)); }};
        void PrintDenseSize() { Log::Print(typeid(T).name(), " Dense size: ", _dense.size()); };
#endif
        private:
        std::vector<T> _dense;
        std::vector<u32> _sparse;
        static constexpr u8 _RESIZE_FACTOR = 2;
    };
}