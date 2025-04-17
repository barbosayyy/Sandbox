#include "Shader.h"
#include "Core/Debug.h"

using namespace SbEngine;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	Debugger::_buffer = "vertex: " + std::string(vertexPath) + " frag: " + std::string(fragmentPath);
	
	this->_shader = Load(File::Read(vertexPath).c_str(), File::Read(fragmentPath).c_str());	
}

GLuint Shader::Load(const char* vertexPath, const char* fragmentPath)
{
	this->_shader = glCreateProgram();
	GLuint vShader = CompileShader(GL_VERTEX_SHADER, vertexPath);
	GLuint fShader = CompileShader(GL_FRAGMENT_SHADER, fragmentPath);

	glAttachShader(this->_shader, vShader);
	glAttachShader(this->_shader, fShader);

	int successful;
	glLinkProgram(this->_shader);
	glGetProgramiv(this->_shader, GL_LINK_STATUS, &successful);
	if (successful == false)
	{
		char infoLog[512];
		glGetProgramInfoLog(this->_shader, 512, NULL, infoLog);

		glDeleteShader(vShader);
		glDeleteShader(fShader);
		
		return -1;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return _shader;
}

void Shader::Use()
{
	glUseProgram(this->_shader);
}

GLuint Shader::CompileShader(GLenum shaderType, const char* shaderSource)
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
		String shaderTypeStr;
		switch(shaderType)
		{
			case(GL_FRAGMENT_SHADER):
				shaderTypeStr = "FRAGMENT";
			break;
			case(GL_VERTEX_SHADER):
				shaderTypeStr = "VERTEX";
			break;
		}
		Debugger::FlushError("Failed to compile shader ", " Shader Type: ", shaderTypeStr, " Path: ", Debugger::_buffer, "\n", infoLog);

		glDeleteShader(shader);
		return 0;
	}
	else
	{
		return shader;
	}
}

void Shader::SetInt(const char* uniformName, GLint value) const
{
	glUniform1i(glGetUniformLocation(this->_shader, uniformName), value);
}

void Shader::SetFloat(const char* uniformName, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(this->_shader, uniformName), value);
}

void Shader::SetVec3(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const
{
	glUniform3f(glGetUniformLocation(this->_shader, uniformName), v1, v2, v3);
}

void Shader::SetVec3(const char* uniformName, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(this->_shader, uniformName), value.x, value.y, value.z);
}

void Shader::SetVec4(const char* uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const
{
	glUniform4f(glGetUniformLocation(this->_shader, uniformName), v1, v2, v3, v4);
}

void Shader::SetMat3(const char* uniformName, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->_shader, uniformName), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* uniformName, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->_shader, uniformName), 1, GL_FALSE, glm::value_ptr(value));
}
