#include "Debug.h"
#include "Base.h"

using namespace SbEngine;

std::string Debugger::_buffer = "";

int Logger::_applicationLogLevel {(int)LogLevel::INFO};

void Logger::SetLogLevel(LogLevel level)
{  
    if(level >= LogLevel::INFO || level <= (LogLevel)0)
        level = LogLevel::INFO;
    Logger::_applicationLogLevel = (int)level;
}

void Debugger::Assert(const String message)
{
    SB_NOT_IMPL;
}

void Logger::FlushLog(){
    SB_NOT_IMPL;
}

bool Logger::IsLoggable(LogLevel level){
    if(u32(level) <= _applicationLogLevel){
        return true;
    }
    return false;
}