#pragma once

#include "Core/Types.h"

#include <iostream>

namespace Sb {

#define SB_ASSERT(x)	  assert(x)
#define SB_NOT_IMPL		  assert("Not implemented yet")
#define SB_S_ASSERT(x, y) static_assert(x, y)
#define SB_TRACE()

	class Log {
	public:
		enum class Level { ERROR = 1, WARNING = 2, INFO = 3, DEBUG = 4 };
		template<typename... Args>
		static void Error(Args... args) {
			if(IsLoggable(Level::ERROR)) {
				std::cerr << '[' << LogLevelToString(Level::ERROR) << ']' << ' ';
				(std::cerr << ... << args) << std::endl;
			}
		}
		template<typename... Args>
		static void Warn(Args... args) {
			if(IsLoggable(Level::WARNING)) {
				std::cout << '[' << LogLevelToString(Level::WARNING) << ']' << ' ';
				(std::cout << ... << args) << std::endl;
			}
		}
		template<typename... Args>
		static void Info(Args... args) {
			if(IsLoggable(Level::INFO)) {
				std::cout << '[' << LogLevelToString(Level::INFO) << ']' << ' ';
				(std::cout << ... << args) << std::endl;
			}
		}
		template<typename... Args>
		static void Print(Args... args) {
			if(IsLoggable(Level::DEBUG)) {
				std::cout << '[' << LogLevelToString(Level::DEBUG) << ']' << ' ';
				(std::cout << ... << args) << std::endl;
			}
		}

		static const String LogLevelToString(Level level) {
			switch(level) {
				case(Level::DEBUG):
					return ("Debug");
					break;
				case(Level::INFO):
					return ("Info");
					break;
				case(Level::WARNING):
					return ("Warning");
					break;
				case(Level::ERROR):
					return ("Error");
					break;
			}
			return ("");
		};
		static void SetLogLevel(Level level);
		static void FlushLog();

	private:
		static int _applicationLogLevel;
		static bool IsLoggable(Level level);
	};

	class Debug {
	public:
		static std::string _buffer;
		template<typename... Args>
		static void FlushError(Args... args) {
			std::cerr << '[' << Log::LogLevelToString(Log::Level::ERROR) << ']' << ' ';
			(std::cerr << ... << args) << std::endl;
			_buffer.clear();
		};

	private:
		// std::chrono::high_resolution_clock _clock;
	};
}