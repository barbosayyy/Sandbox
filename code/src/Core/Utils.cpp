
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>

#include "Utils.h"
#include "Debug.h"

#include "yaml-cpp/yaml.h"

using namespace Sb;

std::filesystem::path File::_currentDirectory = std::filesystem::current_path();

std::string File::Read(const char* filePath) {
	std::string fileContent;
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try{
		file.open(filePath);
		std::stringstream fileStream;

		fileStream << file.rdbuf();

		file.close();

		fileContent = fileStream.str();
	}
	catch (std::ifstream::failure exc) {
		Log::Error("Failed to read file from: ", filePath);
	}

	return fileContent;
}

bool File::Write(const char* content, const String& filePath, const String& fileName) {

	if(!std::filesystem::exists(filePath.c_str())) {
		std::filesystem::create_directories(filePath.c_str());
	}

#ifdef SB_PLATFORM_WIN
	String finalPath = filePath + "\\" + fileName;
#else
	String finalPath = filePath + "/" + fileName;
#endif
	std::ofstream fout(finalPath.c_str());
	if(!fout) {
		return false;
	}
	fout << content;
	return true;
}

String File::GetCurrentDirectory() {
	return _currentDirectory.string();
}

YAML::Node YamlUtil::GetNode(const char* filePath, const char* nodeName) {
	std::ifstream stream(filePath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str()); //TODO -> replace with file::read(filepath)
	if(!data)
		Log::Warn("YamlUtil: Failed to get YAML node from string: ", filePath);

	return data[nodeName];
}

/*
	Gets int in given range, inclusive
*/
int Random::GetRange(int from, int to) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(from, to);
	return int(dist(gen));
}
