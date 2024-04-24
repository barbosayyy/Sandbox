#pragma once

#include "types.h"

namespace Sandbox{

    enum class LogLevel{
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    class Logger{
    public:
        static void Message(LogLevel level, const char* message);
    private:
        static String LogLevelToString(LogLevel level);
    };
}
