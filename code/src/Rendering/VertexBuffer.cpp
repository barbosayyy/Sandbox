#include "VertexBuffer.h"
#include "Core/Debug.h"

using namespace SbEngine;

VertexBuffer::VertexBuffer() 
{
	
}

VertexBuffer::VertexBuffer(float* vertices, GLsizei vertexCount)
{
	this->_vertices = vertices;
	this->_vertexCount = vertexCount;
	VertexBuffer::CreateBuffer(this->_vertices, this->_vertexCount);
}

// VertexBuffer::VertexBuffer(float* vertices, GLsizei vertexCount, size_t dataSize)
// {
// 	this->_vertices = vertices;
// 	this->_vertexCount = vertexCount;
// 	VertexBuffer::CreateBuffer(this->_vertices, this->_vertexCount, dataSize);
// }

VertexBuffer::VertexBuffer(std::vector<float> vertices) : _verticesVec{vertices}
{
	SB_NOT_IMPL;
	this->_vertexCount = 0;
	VertexBuffer::CreateBuffer(this->_verticesVec);
}

VertexBuffer::~VertexBuffer() 
{
	glDeleteVertexArrays(1, &this->_vao);
	glDeleteBuffers(1, &_vbo);
}

void VertexBuffer::CreateBuffer(float* vertices, GLsizei vertexCount)
{
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &this->_vbo);

	glBindVertexArray(this->_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::CreateBuffer(std::vector<float> vertices)
{
	glGenVertexArrays(1, &this->_vao);
	glGenBuffers(1, &this->_vbo);

	glBindVertexArray(this->_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(this->_vao);
}

void VertexBuffer::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
}