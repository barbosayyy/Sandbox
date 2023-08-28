#pragma once

#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(float* vertices, GLsizei vertexCount);
	~VertexBuffer();

	void bind();
	void draw();
private:
	GLuint vbo = 0;
	GLuint vao = 0;
	float* vertices;
	GLsizei vertexCount = 0;

	void createBuffer(float* vertices, GLsizei vertexCount);
};