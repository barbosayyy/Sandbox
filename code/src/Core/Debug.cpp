#include "Debug.h"
#include "Base.h"

using namespace Sb;

std::string Debug::_buffer = "";

int Log::_applicationLogLevel {(int)Level::INFO};

void Log::SetLogLevel(Level level)
{  
    if(level >= Level::DEBUG || level <= (Level)0)
        level = Level::DEBUG;
    Log::_applicationLogLevel = (int)level;
}

void Log::FlushLog(){
    SB_NOT_IMPL;
}

bool Log::IsLoggable(Level level){
    if(u32(level) <= _applicationLogLevel){
        return true;
    }
    return false;
}