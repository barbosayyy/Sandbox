
#include "utils.h"

std::map<uint8_t, GLenum> Resources::TextureUnitMap = {
		{0, GL_TEXTURE0},
		{1, GL_TEXTURE1},
		{2, GL_TEXTURE2},
		{3, GL_TEXTURE3},
		{4, GL_TEXTURE4},
		{5, GL_TEXTURE5},
		{6, GL_TEXTURE6},
		{7, GL_TEXTURE7}
};

std::filesystem::path File::currentDirectory = std::filesystem::current_path();

std::string File::read(const char* filePath)
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
		// To do - placeholder for logger
		std::cout << "ERROR::FILE_READ::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	return fileContent;
}