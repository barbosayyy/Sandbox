#pragma once

#include "Core/Types.h"
#include "Material.h"
#include "Rendering/Renderer.h"

#include <vector>

namespace Sb {

	class Mesh {
	public:
		Mesh();
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
		~Mesh();

		void Draw(Renderer* renderer, vec3 pos, vec3 rot, vec3 scale);
		
		void SetTextureMap(u32 assetID, TextureType type);
		
		private:
		
		void CreateMesh();
		
		std::vector<Vertex> _vertices;
		std::vector<u32> _indices;
		unsigned int _vao;
		Material _material;
		// unsigned int _vbo;
		// unsigned int _ebo;

	};
}

