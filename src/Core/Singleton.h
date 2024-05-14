#pragma once

template<typename T, typename ...Args>
class Singleton{
    public:
        //static T* GetInstance(){
        //    if(_instance == nullptr)
        //    {
        //        _instance = new T();
        //    }
        //	return _instance;
        //}
        static T* GetInstance(){
           return _instance ? _instance : (_instance = new T());
        }
        static T* GetInstance(Args...args){
            return _instance ? _instance : (_instance = new T(std::forward<decltype(args)>(args)...));
        }

        // TODO Add destructor for instance

        //static T* GetInstance(){
        //    return _instance;
        //}

        Singleton<T>(const Singleton<T>&) = delete;
        Singleton<T>& operator=(const Singleton<T>&) = delete;
    protected:
        static T* _instance;
        Singleton<T>(){};
};

template<typename T, typename ...Args>
T* Singleton<T, Args...>::_instance = nullptr;