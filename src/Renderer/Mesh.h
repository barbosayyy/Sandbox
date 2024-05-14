#pragma once

#include <vector>
#include "../Math/Vectors.h"
#include "Texture.h"
#include "Shader.h"
#include "../Core/Types.h"
#include <map>
#include <iterator>

namespace Sandbox{
	class Mesh {
	public:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		std::vector<Texture> _textures;
		Shader& _shader;
	
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures, Shader& _shader);
		~Mesh();
		
		void Draw();
		void BindTextures();
	
	private:
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
	
		void CreateMesh();
	};
}

