#pragma once

#include <iostream>
#include <GL/glew.h>
#include "utils.h"

class Shader {
public:
	GLuint shader;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
private:
	GLuint compileShader(GLenum shaderType, const char* shaderSource);
	GLuint load(const char* vertexPath, const char* fragmentPath);
};

//class ShaderProgram {
//public:
//	ShaderProgram();
//	~ShaderProgram();
//
//	unsigned int sProgram;
//
//	void attachShader(unsigned int sProgram, unsigned int shader);
//
//	unsigned int loadProgram(unsigned int sProgram);
//};