#pragma once

#include <string_view>
#include <vector>
#include "../Core/Base.h"
#include <glew/glew.h>

namespace Sandbox{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(unsigned int* indices, unsigned int indexCount);
		IndexBuffer(unsigned int* indices);
		IndexBuffer(std::vector<unsigned int> indices);

		~IndexBuffer();

		void Draw();
	private:
		GLuint _ebo;
		GLuint* _indices;
		GLsizei _count;
		std::vector<unsigned int> _indicesVec;

		void Bind(bool bind);

		void CreateBuffer(unsigned int* indices, unsigned int indexCount);
		void CreateBuffer(unsigned int* indices);
		void CreateBuffer(std::vector<unsigned int> indices);
	};
}



