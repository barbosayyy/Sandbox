#pragma once

#include "Core/Types.h"
#include "NewMaterial.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Rendering/Renderer.h"

#include <vector>

namespace Sb {

	class Mesh {
	public:
	
		Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, NewMaterial _material);
		Mesh(float* _vertices, const u32* _indices, NewMaterial material);
		~Mesh();

		void Draw(Renderer* renderer, vec3 pos);
		
		void BindTextures(Shader* shader);
		
	private:

		void CreateMesh();
		
		std::vector<Vertex> _vertices;
		std::vector<u32> _indices;
		NewMaterial _material;
		unsigned int _vbo;
		unsigned int _vao;
		unsigned int _ebo;
	};
}

