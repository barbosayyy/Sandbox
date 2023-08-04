#pragma once

#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(float vertices[], GLsizei vertexCount);
	~VertexBuffer();

	void draw();
private:
	GLuint vbo;
	GLuint vao;
	float* vertices;
	GLsizei vertexCount;

	void createBuffer(float vertices[], GLsizei vertexCount);
};