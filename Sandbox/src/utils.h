#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <filesystem>

class File
{
private:
	static std::filesystem::path currentDirectory;
public:
	static std::string read(const char* filePath);
};