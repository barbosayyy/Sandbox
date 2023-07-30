#include "shaders.h"

unsigned int compileShaders(GLenum shaderType, const char* shaderSource)
{
	auto shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int successful;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	else
	{
		return 1;
	}
}