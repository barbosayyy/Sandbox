
#include "Utils.h"
#include "Debug.h"

using namespace Sandbox;

std::map<uint8_t, GLenum> Resources::_textureUnitMap = {
		{0, GL_TEXTURE0},
		{1, GL_TEXTURE1},
		{2, GL_TEXTURE2},
		{3, GL_TEXTURE3},
		{4, GL_TEXTURE4},
		{5, GL_TEXTURE5},
		{6, GL_TEXTURE6},
		{7, GL_TEXTURE7}
};

std::map<TextureType, String> Resources::_textureTypeMap = {
	{TextureType::DIFFUSE, "diffuse"},
	{TextureType::SPECULAR,"specular"},
	{TextureType::EMISSIVE,"emissive"},
};

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
