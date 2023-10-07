#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include "glew/glew.h"
#include "texture.h"
#include "types.h"

static class Resources
{
public:
	static std::map<uint8_t, GLenum> TextureUnitMap;
	static std::map<Texture::TextureType, String> TextureTypeMap;
};

class File
{
private:
	static std::filesystem::path currentDirectory;
public:
	static std::string read(const char* filePath);
};