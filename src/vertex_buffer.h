#pragma once

#include <iostream>
#include <glew/glew.h>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(float* vertices, GLsizei vertexCount);
	VertexBuffer(std::vector<float> vertices);
	~VertexBuffer();

	void bind();
	void draw();
private:
	GLuint vbo = 0;
	GLuint vao = 0;
	float* vertices;
	std::vector<float> verticesVec;
	GLsizei vertexCount = 0;

	void createBuffer(float* vertices, GLsizei vertexCount);
	void createBuffer(std::vector<float> vertices);
};