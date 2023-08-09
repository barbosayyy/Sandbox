#include "vertex_buffer.h"

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

}

void VertexBuffer::createBuffer(float* vertices, GLsizei vertexCount)
{
	glGenBuffers(1, &this->vbo);
	glGenVertexArrays(1, &this->vao);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind()
{
	glBindVertexArray(this->vao);
}