#pragma once

#include "../Core/Base.h"
#include "../Core/Types.h"
#include <glew/glew.h>

namespace Sandbox{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(float* vertices, GLsizei vertexCount);
		VertexBuffer(std::vector<float> vertices);
		~VertexBuffer();

		void Bind();
		void Draw();
	private:
		GLuint _vbo = 0;
		GLuint _vao = 0;
		float* _vertices;
		std::vector<float> _verticesVec;
		GLsizei _vertexCount = 0;

		void CreateBuffer(float* vertices, GLsizei vertexCount);
		void CreateBuffer(float* vertices, GLsizei vertexCount, size_t dataSize);
		void CreateBuffer(std::vector<float> vertices);
	};
}