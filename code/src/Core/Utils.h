#pragma once

#include "Core/Types.h"

#define YAML_CPP_STATIC_DEFINE
#include "yaml-cpp/node/node.h"

#include <string>
#include <filesystem>

namespace Sb {

	class File{
	private:
		static std::filesystem::path _currentDirectory;
	public:
		static std::string Read(const char* filePath);
		static bool Write(const char* content, const String& filePath, const String& fileName);
		static String GetCurrentDirectory();
	};

	class YamlUtil{
	private:
		
	public:
		static YAML::Node GetNode(const char* filePath, const char* nodeName);
	};
	
	class Random{
	public:
		// Range inclusive
		static int GetRange(int from, int to);
	};

	class StringParser {
	public:
		static u64 HexToU64(const String& string);
	};

}

