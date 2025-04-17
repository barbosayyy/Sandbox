#pragma once

#include <forward_list>
#include <memory>

// Singleton pattern class for creating single instance objects
// Derived classes must implement their own destructor
template<typename T, typename ...Args>
class Singleton{
    public:

        // Returns a reference to singleton internal smart pointer
        // Smart pointer is managed internally
        static T& GetInstance(){
            if(!_instance){
                _instance = std::make_unique<T>();
            }
            return *_instance;
        }

        static T& GetInstance(Args...args){
            if(!_instance){
                _instance = std::make_unique<T>(std::forward<decltype(args)>(args)...);
            }
            return *_instance;
        }

        // Singleton<T>(const Singleton<T>&) = delete;
        // Singleton<T>& operator=(const Singleton<T>&) = delete;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
    protected:
        // TODO: Constructor could set instance? no
        //          if(_instance == nullptr)
        //              _instance == this;

        // Singleton<T>() = default;
        Singleton() = default;
        virtual ~Singleton() = default;
    private:
        static std::unique_ptr<T> _instance;
};

template<typename T, typename ...Args>
std::unique_ptr<T> Singleton<T, Args...>::_instance = nullptr;