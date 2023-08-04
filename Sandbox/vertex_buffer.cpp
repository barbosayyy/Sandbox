#include "vertex_buffer.h"

VertexBuffer::VertexBuffer() 
{
	
}

VertexBuffer::VertexBuffer(float vertices[], GLsizei vertexCount)
{
	this->vertices = vertices;
	this->vertexCount = vertexCount;
	VertexBuffer::createBuffer(vertices, vertexCount);
}

VertexBuffer::~VertexBuffer() 
{

}

void VertexBuffer::createBuffer(float vertices[], GLsizei vertexCount)
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * vertexCount, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::draw()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}