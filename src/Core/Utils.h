#pragma once

#include <string>
#include <filesystem>
#include "../Core/Types.h"
#include "yaml-cpp/node/node.h"

namespace Sandbox{
	class File
	{
	private:
		static std::filesystem::path _currentDirectory;
	public:
		static std::string Read(const char* filePath);
		static String GetCurrentPath();
	};

	class YamlUtil
	{
	private:
		
	public:	
		static YAML::Node GetNode(const char* filePath, const char* nodeName);
	};
}

