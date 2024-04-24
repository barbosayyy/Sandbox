#pragma once

#include <vector>
#include <glew/glew.h>

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(unsigned int* indices, unsigned int indicesCount);
	IndexBuffer(unsigned int* indices);
	IndexBuffer(std::vector<unsigned int> indices);

	~IndexBuffer();

	void draw();
private:
	GLuint ebo;
	GLuint* indices;
	GLsizei count;
	std::vector<unsigned int> indicesVec;

	void bind(bool bind);

	void createBuffer(unsigned int* indices, unsigned int indicesCount);
	void createBuffer(unsigned int* indices);
	void createBuffer(std::vector<unsigned int> indices);
};

