#pragma once

#include "Base.h"
#include "Types.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <chrono>

namespace Sandbox{

    enum class LogLevel{
        LOGGING_ERROR   = 1,
        CRITICAL        = 2,
        ERROR           = 3,
        WARNING         = 4,
        INFO            = 5
    };

    static String LogLevelToString(LogLevel level){
        String ret;

        switch(level)
        {
            case(LogLevel::INFO):
                ret = "Info";
            break;
            case(LogLevel::WARNING):
                ret = "Warning";
            break;
            case(LogLevel::ERROR):
                ret = "Error";
            break;
            case(LogLevel::CRITICAL):
                ret = "Critical Error";
            case(LogLevel::LOGGING_ERROR):
                ret = "Logging Error";
            break;
        }
        return ret;
    };

    class Logger{
    public:
        template <typename ...Args>
        static void Trace(LogLevel level, Args... args){

            // Might throw linking error here
            if((u32)level > Logger::applicationLogLevel)
                return;
            if(LogLevelToString(level).empty()){
                Logger::Trace(LogLevel::LOGGING_ERROR, "Provide a Log Level");
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

    class Debugger{
    public:
        static void Assert(const String message);
        template<typename ...Args>
        static void FlushError(Args... args){
            std::cerr << '[' << LogLevelToString(LogLevel::ERROR) << ']' << ' ';
            (std::cerr << ... << args) << std::endl;
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