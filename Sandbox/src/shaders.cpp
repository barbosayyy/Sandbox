#include "shaders.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	this->shader = load(File::read(vertexPath).c_str(), File::read(fragmentPath).c_str());
}

GLuint Shader::load(const char* vertexPath, const char* fragmentPath)
{
	this->shader = glCreateProgram();
	GLuint vShader = compileShader(GL_VERTEX_SHADER, vertexPath);
	GLuint fShader = compileShader(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(this->shader, vShader);
	glAttachShader(this->shader, fShader);

	int successful;
	glLinkProgram(this->shader);
	glGetProgramiv(this->shader, GL_LINK_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetProgramInfoLog(this->shader, 512, NULL, infoLog);
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return shader;
}

void Shader::use()
{
	glUseProgram(this->shader);
}

GLuint Shader::compileShader(GLenum shaderType, const char* shaderSource)
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