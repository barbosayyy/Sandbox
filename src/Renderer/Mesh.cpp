#include "Mesh.h"
#include "Texture.h"

using namespace Sandbox;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : _vertices(vertices), _indices(indices),_textures(textures)
{
	CreateMesh();
}

Mesh::~Mesh()
{

}

void Mesh::CreateMesh()	
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	if(_vertices.size() > 0){
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
	}
	else{
		std::cout << "Mesh_createMesh: Vertex vector is empty!" << std::endl;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
	if (_vertices.size() > 0)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);
}

void Mesh::BindTextures(Shader* shader)
{
	int tmpDiffuse{ 1 };
	int tmpSpecular{ 1 };
	if (this->_textures.size() > 0)
	{
		u8 i {0};
		String n;
		String name;
		String final;
		for (Texture texture : _textures)
		{
			glActiveTexture(textureUnitMap.at(i));
			
			std::map<TextureType, String>::iterator it;
			it = textureTypeMap.find(_textures.at(i)._type);
			name = it->second;
			//// TODO this can be refactored by casting String
			//String nr;
			//String name = it->second;
			if (it->first == TextureType::DIFFUSE)
				n = std::to_string(tmpDiffuse++);
			else if(it->first == TextureType::SPECULAR)
				n = std::to_string(tmpSpecular++);
				
			shader->SetInt(String(String("texture_")+name+n).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, _textures.at(i)._texture);
			i++;
		}
		glActiveTexture(textureUnitMap.at(0));
	}
}

void Mesh::Draw(Shader* shader)
{
	BindTextures(shader);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}