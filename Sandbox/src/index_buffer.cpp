#include "index_buffer.h"

IndexBuffer::IndexBuffer()
{

}

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int indicesCount)
{
	this->count = indicesCount;
	this->indices = indices;

	IndexBuffer::createBuffer(this->indices, this->count);
}

IndexBuffer::~IndexBuffer()
{

}

void IndexBuffer::createBuffer(unsigned int* indices, unsigned int indicesCount)
{
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void IndexBuffer::bind(bool bind)
{
	if (bind)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void IndexBuffer::draw()
{
	bind(true);
	glDrawElements(GL_TRIANGLES, this->count, GL_UNSIGNED_INT, 0);
}