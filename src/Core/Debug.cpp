#include "Debug.h"
#include "Base.h"
#include <cassert>

using namespace Sandbox;

std::string Debugger::_buffer = "";

int Logger::applicationLogLevel {(u32)LogLevel::RUNTIME}; 

void Logger::SetLogLevel(LogLevel level)
{  
    if(level >= LogLevel::RUNTIME || level <= (LogLevel)0)
        level = LogLevel::CRITICAL;
    Logger::applicationLogLevel = (u32)level;
}

void Debugger::Assert(const String message)
{
    
}

void Logger::FlushLog(){
    SB_NOT_IMPL;
}