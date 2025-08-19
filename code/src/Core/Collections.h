#pragma once

#include "Core/Debug.h"
#include <vector>

namespace Sb {
    template<typename T>
    struct SparseSet{
    public:
        void Insert(size_t element, T data) {
            if(element > _sparse.size()-1 ){
                for(int i = _sparse.size(); i < element; i++) {
                    _sparse.emplace_back(-1);
                }
            }
            else if(_sparse.at(element) > -1){
                Sb::Log::Warn("Collections; Sparse Set: Sparse already points to value in dense set");
                return;
            }

            _dense.emplace_back(data);
            if(_dense.size() > 0){
                size_t i = _dense.size()-1;
                _sparse.at(element) = i;
            }
        }
        void Remove(size_t element) {
            Log::Warn("Collections: SparseSet.Remove(size_t element) is not implemented!");
        }
        T Get(size_t element) {
            if(element < _sparse.size()){
                if(_sparse.at(element) != -1){
                    return _dense.at(_sparse.at(element));
                }
            }
        }
        void Clear() {
            SB_ASSERT("");
        }
    private:
        std::vector<T> _dense;
        std::vector<size_t> _sparse;
    };
}