#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Core/Types.h"
#include "Renderer.h"

#include <vector>

namespace SbEngine{

	class Mesh {
		
	public:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		std::vector<Texture> _textures;

		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures);
		~Mesh();
		
		void Draw(Shader* shader, Renderer* renderer);
		void BindTextures(Shader* shader);
	
	private:
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
	
		void CreateMesh();
	};
}

