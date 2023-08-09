#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(unsigned int* indices, unsigned int indicesCount);
	~IndexBuffer();

	void draw();
private:
	GLuint ebo;
	GLuint* indices;
	GLsizei count;

	void bind(bool bind);

	void createBuffer(unsigned int* indices, unsigned int indicesCount);
};

