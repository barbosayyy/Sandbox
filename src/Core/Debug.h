#pragma once

#include "Base.h"
#include "Types.h"
#include <cstddef>
#include <iostream>
#include <string>

namespace Sandbox{

    enum class LogLevel{
        CRITICAL        = 1,
        ERROR           = 2,
        WARNING         = 3,
        RUNTIME         = 4
    };

    static String LogLevelToString(LogLevel level){
        String ret;

        switch(level)
        {
            case(LogLevel::RUNTIME):
                ret = "Runtime";
            break;
            case(LogLevel::WARNING):
                ret = "Warning";
            break;
            case(LogLevel::ERROR):
                ret = "Error";
            break;
            case(LogLevel::CRITICAL):
                ret = "Critical Error";
        }
        return ret;
    };
 
    // (Static) - Class for logging engine behavior

    class Logger{
    public:
        template <typename ...Args>
        static void Trace(LogLevel level, Args... args){

            // Might throw linking error here
            if((u32)level > Logger::applicationLogLevel)
                return;
            if(LogLevelToString(level).empty()){
                Logger::Trace(LogLevel::CRITICAL, "Logger: Provide a Log Level");
                return;
            }
            std::cout << '[' << LogLevelToString(level) << ']' << ' ';
            (std::cout << ... << args) << std::endl;
        };

        static void SetLogLevel(LogLevel level);
        static void FlushLog();
    private:
        static int applicationLogLevel;
    };

    // (Static) - Use for runtime debugging

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
        template <typename ...Args>
        static void Print(Args... args){
           std::cout << "[Debug]" << ' ';
           (std::cout << ... << args) << std::endl;
        }
    private:
        // std::chrono::high_resolution_clock _clockTime;
    };
}


// Test
#define SB_TRACE_INFO
#define SB_TRACE_WARNING
#define SB_TRACE_ERROR
#define SB_TRACE_CRITICAL