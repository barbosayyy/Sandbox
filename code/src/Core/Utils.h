#pragma once

#include "Core/Types.h"
#include "yaml-cpp/node/node.h"

#include <string>
#include <filesystem>
#include <random>

namespace SbEngine{

	class File{
	private:
		static std::filesystem::path _currentDirectory;
	public:
		static std::string Read(const char* filePath);
		static String GetCurrentPath();
	};

	class YamlUtil{
	private:
		
	public:	
		static YAML::Node GetNode(const char* filePath, const char* nodeName);
	};
	
	class Random{
	public:
		// Inclusive
		static int GetRange(int from, int to);
	};
}

