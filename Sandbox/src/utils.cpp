
#include "utils.h"

//File

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