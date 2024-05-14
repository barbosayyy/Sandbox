#include "mesh.h"

using namespace Sandbox;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Shader& shader) : _shader(shader)
{
	this->_vertices = vertices;
	this->_indices = indices;
	this->_textures = textures;

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
	if(_vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
	else
		std::cout << "Mesh_createMesh: Vertex vector is empty!" << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	if (_indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
	else
		std::cout << "Mesh_createMesh: Indices vector is empty!" << std::endl;
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

void Mesh::BindTextures()
{
	int aux_diffuse{ 1 };
	int aux_specular{ 1 };
	int aux_emissive{ 1 };
	String mat = "material.";
	if (this->_textures.size() > 0)
	{
		for (unsigned int i = 0; i < _textures.size(); i++)
		{
			glActiveTexture(Resources::_textureUnitMap.at(i));
			std::map<TextureType, String>::iterator it;
			it = Resources::_textureTypeMap.find(_textures.at(i)._type);
			// TODO this can be refactored by casting String
			String nr;
			String name = it->second;
			if (it->first == TextureType::DIFFUSE)
				nr = std::to_string(aux_diffuse++);
			else if(it->first == TextureType::SPECULAR)
				nr = std::to_string(aux_specular++);
			else if (it->first == TextureType::EMISSIVE)
				nr = std::to_string(aux_emissive++);
			this->_shader.SetInt((mat+name+nr).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, _textures.at(i)._texture);
		}
		glActiveTexture(Resources::_textureUnitMap.at(0));
	}
}

void Mesh::Draw()
{
	BindTextures();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}