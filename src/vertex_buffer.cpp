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

VertexBuffer::VertexBuffer(std::vector<float> vertices)
{
	this->verticesVec = vertices;
	this->vertexCount = 0;
	VertexBuffer::createBuffer(this->verticesVec);
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

	// FIXME Data size
	glBufferData(GL_ARRAY_BUFFER, 288*sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::createBuffer(std::vector<float> vertices)
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind()
{
	glBindVertexArray(this->vao);
}

void VertexBuffer::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}