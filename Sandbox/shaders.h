#pragma once

#include <iostream>
#include <GL/glew.h>

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	unsigned int sProgram;

	void attachShader(unsigned int sProgram, unsigned int shader);

	unsigned int loadProgram(unsigned int sProgram);
};

unsigned int compileShader(GLenum shaderType, const char* shaderSource);

void deleteShader(unsigned int shader);