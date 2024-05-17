#pragma once

#include <forward_list>

// Singleton pattern class for creating single instance objects
// Derived classes must implement their own destructor
template<typename T, typename ...Args>
class Singleton{
    public:
        static T* GetInstance(){
           return _instance ? _instance : (_instance = new T());
        }
        static T* GetInstance(Args...args){
            return _instance ? _instance : (_instance = new T(std::forward<decltype(args)>(args)...));
        }

        Singleton<T>(const Singleton<T>&) = delete;
        Singleton<T>& operator=(const Singleton<T>&) = delete;
    protected:
        static T* _instance;
        // TODO: Constructor could set instance?
        //          if(_instance == nullptr)
        //              _instance == this;

        Singleton<T>(){};
};

template<typename T, typename ...Args>
T* Singleton<T, Args...>::_instance = nullptr;