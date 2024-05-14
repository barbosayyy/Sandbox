#include "Debug.h"
#include <cassert>

using namespace Sandbox;

int Logger::applicationLogLevel {(u32)LogLevel::INFO}; 

void Logger::SetLogLevel(LogLevel level)
{  
    if(level >= LogLevel::INFO || level <= (LogLevel)0)
        level = LogLevel::CRITICAL;
    Logger::applicationLogLevel = (u32)level;
}

void Debugger::Assert(const String message)
{
    
}

void Logger::FlushLog(){
    assert("Not implemented yet");
}