#include "IndexBuffer.h"

using namespace Sandbox;

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int indexCount)
{
	this->_count = indexCount;
	this->_indices = indices;

	IndexBuffer::CreateBuffer(this->_indices, this->_count);
}

IndexBuffer::IndexBuffer(unsigned int* indices)
{
	IndexBuffer::CreateBuffer(indices);
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> indices) : _indicesVec{indices}
{
	this->_count = _indicesVec.size();
	IndexBuffer::CreateBuffer(_indicesVec);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_ebo);
}

void IndexBuffer::CreateBuffer(unsigned int* indices, unsigned int indicesCount)
{
	glGenBuffers(1, &this->_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void IndexBuffer::CreateBuffer(unsigned int* indices)
{
	glGenBuffers(1, &this->_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void IndexBuffer::CreateBuffer(std::vector<unsigned int> indices)
{
	glGenBuffers(1, &this->_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void IndexBuffer::Bind(bool bind)
{
	if (bind)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void IndexBuffer::Draw()
{
	Bind(true);
	glDrawElements(GL_TRIANGLES, this->_count, GL_UNSIGNED_INT, 0);
}