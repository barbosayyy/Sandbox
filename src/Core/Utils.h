#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include "glew/glew.h"
#include "../Renderer/Texture.h"
#include "../Core/Types.h"
#include "yaml-cpp/yaml.h"

namespace Sandbox{
	class Resources
	{
	public:
		static std::map<uint8_t, GLenum> _textureUnitMap;
		static std::map<TextureType, String> _textureTypeMap;
	};

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

