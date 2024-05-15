
#include <fstream>
#include <sstream>

#include "Utils.h"
#include "Debug.h"

#include "yaml-cpp/yaml.h"

using namespace Sandbox;

std::filesystem::path File::_currentDirectory = std::filesystem::current_path();

std::string File::Read(const char* filePath)
{
	std::string fileContent;
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		file.open(filePath);
		std::stringstream fileStream;

		fileStream << file.rdbuf();

		file.close();

		fileContent = fileStream.str();
	}
	catch (std::ifstream::failure exc)
	{
		Logger::Trace(LogLevel::ERROR, "Failed to read file from: ", filePath);
	}

	return fileContent;
}

String File::GetCurrentPath()
{
	return _currentDirectory.string();
}

YAML::Node YamlUtil::GetNode(const char* filePath, const char* nodeName)
{
	std::ifstream stream(filePath);
	std::stringstream strStream;
	strStream << stream.rdbuf();

	YAML::Node data = YAML::Load(strStream.str()); //TODO -> replace with file::read(filepath)
	if(!data)
		Logger::Trace(LogLevel::WARNING, "YamlUtil: Failed to get YAML node from string: ", filePath);

	return data[nodeName];
}
