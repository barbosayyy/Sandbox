#include "Collections.h"

#include "Core/Debug.h"

namespace SbEngine {
    template<typename T>
    void SparseSet<T>::Insert(size_t element, T data){
        // element to dense set
        // get element index from dense set
        // store element

        if(element > _sparse.size()-1 ){
            for(int i = _sparse.size(); i < element; i++){
                _sparse.emplace_back(-1);
            }
        }
        else if(_sparse.at(element) > -1){
            Logger::Warn("Collections; Sparse Set: Sparse already points to value in dense set");
            return;
        }

        _dense.emplace_back(data);
        if(_dense.size() > 0){
            size_t i = _dense.size()-1;
            _sparse.at(element) = i;
        }
    }

    template<typename T>
    void SparseSet<T>::Remove(size_t element){
        SB_ASSERT("");
    }

    template<typename T>
    T SparseSet<T>::Get(size_t element){
        if(element < _sparse.size()){
            if(_sparse.at(element) != -1){
                return _dense.at(_sparse.at(element));
            }
        }
    }

    template<typename T>
    void SparseSet<T>::Clear(){
        SB_ASSERT("");
    }
}

