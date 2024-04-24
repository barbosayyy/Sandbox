#include <iostream>
#include "logger.h"
#include "types.h"
#include <string>

using namespace Sandbox;

void Logger::Message(LogLevel level, const char* message){
    String logLevel = LogLevelToString(level);
    if(!logLevel.empty()){
        std::cout << "["+(std::string)LogLevelToString(level)+"]" + " " + message;
    }
};

String Logger::LogLevelToString(LogLevel level)
{
    String ret;
    switch(level)
    {
        case(LogLevel::DEBUG):
            ret = "Debug";
        break;
        case(LogLevel::INFO):
            ret = "Info";
        break;
        case(LogLevel::WARNING):
            ret = "Warning";
        break;
        case(LogLevel::ERROR):
            ret = "Error";
        break;
    }
    return ret;
}