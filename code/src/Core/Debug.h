#pragma once

#include "Core/Types.h"

#include <iostream>

namespace SbEngine{

    #define SB_ASSERT(x)					assert(x)
    #define SB_NOT_IMPL						assert("Not implemented yet")
    #define SB_S_ASSERT(x, y)				static_assert(x, y)

    enum class LogLevel{
        ERROR           = 1,
        WARNING         = 2,
        INFO            = 3
    };

    static String LogLevelToString(LogLevel level){
        switch(level)
        {
            case(LogLevel::INFO):
                return("Info");
            break;
            case(LogLevel::WARNING):
                return("Warning");
            break;
            case(LogLevel::ERROR):
                return("Error");
            break;
        }
        return("");
    };

    class Logger{
    public:
        template <typename ...Args>
        static void Error(Args... args){
            if(IsLoggable(LogLevel::ERROR)){
                std::cerr << '[' << LogLevelToString(LogLevel::ERROR) << ']' << ' ';
                (std::cerr << ... << args) << std::endl;
            }
        }
        template <typename ...Args>
        static void Warn(Args... args){
            if(IsLoggable(LogLevel::WARNING)){
                std::cout << '[' << LogLevelToString(LogLevel::WARNING) << ']' << ' ';
                (std::cout << ... << args) << std::endl; 
            }
        }
        template <typename ...Args>
        static void Print(Args... args){
            if(IsLoggable(LogLevel::INFO)){
                std::cout << '[' << LogLevelToString(LogLevel::INFO) << ']' << ' ';
                (std::cout << ... << args) << std::endl;
            }
        }

        // Logging to file
        /*
        template <typename ...Args>
        static void Log(Args... args){}
        */

        static void SetLogLevel(LogLevel level);
        static void FlushLog();
    private:
        static int _applicationLogLevel;
        static bool IsLoggable(LogLevel level);
    };

    class Debugger{
    public:
        static std::string _buffer;
        static void Assert(const String message);
        template<typename ...Args>
        static void FlushError(Args... args){
            std::cerr << '[' << LogLevelToString(LogLevel::ERROR) << ']' << ' ';
            (std::cerr << ... << args) << std::endl;
                _buffer.clear();
        };
    private:
        // std::chrono::high_resolution_clock _clock;
    };

    #define SB_TRACE()
}