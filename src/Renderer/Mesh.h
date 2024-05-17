#pragma once

#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "../Core/Types.h"

namespace Sandbox{

	class Mesh {
	public:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		std::vector<Texture> _textures;

		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
		~Mesh();
		
		void Draw(Shader* shader);
		void BindTextures(Shader* shader);
	
	private:
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
	
		void CreateMesh();
	};
}

