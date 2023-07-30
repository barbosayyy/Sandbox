#pragma once

#include <GL/glew.h>

class BOUtils
{
public:
	static GLuint createBO(GLsizeiptr size, const GLvoid* data, GLenum usage);
};