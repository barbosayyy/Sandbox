#include "vertex_buffer.h"
#include <iostream>
VertexBuffer::VertexBuffer() 
{
	
}

VertexBuffer::VertexBuffer(float* vertices, GLsizei vertexCount)
{
	this->vertices = vertices;
	this->vertexCount = vertexCount;
	VertexBuffer::createBuffer(this->vertices, this->vertexCount);
}

VertexBuffer::~VertexBuffer() 
{
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::createBuffer(float* vertices, GLsizei vertexCount)
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::bind()
{
	glBindVertexArray(this->vao);
}