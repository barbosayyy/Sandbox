#include "Debug.h"
#include "Base.h"

using namespace Sb;

std::string Debug::_buffer = "";

int Log::_applicationLogLevel {(int)LogLevel::INFO};

void Log::SetLogLevel(LogLevel level)
{  
    if(level >= LogLevel::DEBUG || level <= (LogLevel)0)
        level = LogLevel::DEBUG;
    Log::_applicationLogLevel = (int)level;
}

void Debug::Assert(const String message)
{
    SB_NOT_IMPL;
}

void Log::FlushLog(){
    SB_NOT_IMPL;
}

bool Log::IsLoggable(LogLevel level){
    if(u32(level) <= _applicationLogLevel){
        return true;
    }
    return false;
}