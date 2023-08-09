#include "shaders.h"

ShaderProgram::ShaderProgram()
{
	ShaderProgram::sProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	
}

void ShaderProgram::attachShader(unsigned int sProgram, unsigned int shader)
{
	glAttachShader(sProgram, shader);
}

unsigned int ShaderProgram::loadProgram(unsigned int sProgram)
{
	int successful;
	glLinkProgram(sProgram);
	glGetProgramiv(sProgram, GL_LINK_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetProgramInfoLog(sProgram, 512, NULL, infoLog);
	}

	glUseProgram(sProgram);

	return sProgram;
}

unsigned int compileShader(GLenum shaderType, const char* shaderSource)
{
	unsigned int shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int successful;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error: " << shaderType << "\n" << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	else
	{
		return shader;
	}
}

void deleteShader(unsigned int shader)
{
	glDeleteShader(shader);
}