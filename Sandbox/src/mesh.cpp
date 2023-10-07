#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Shader& shader) : shader(shader)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	createMesh();
}

Mesh::~Mesh()
{

}

void Mesh::createMesh()	
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if(vertices.size() > 0)
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	else
		std::cout << "Mesh_createMesh: Vertex vector is empty!" << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	if (indices.size() > 0)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	else
		std::cout << "Mesh_createMesh: Indices vector is empty!" << std::endl;
	if (vertices.size() > 0)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoords));
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);
}

void Mesh::bindTextures()
{
	int aux_diffuse{ 1 };
	int aux_specular{ 1 };
	int aux_emissive{ 1 };
	String mat = "material.";
	if (this->textures.size() > 0)
	{
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(Resources::TextureUnitMap.at(i));
			std::map<Texture::TextureType, String>::iterator it;
			it = Resources::TextureTypeMap.find(textures.at(i).type);
			String nr;
			String name = it->second;
			if (it->first == Texture::TextureType::DIFFUSE)
				nr = std::to_string(aux_diffuse++);
			else if(it->first == Texture::TextureType::SPECULAR)
				nr = std::to_string(aux_specular++);
			else if (it->first == Texture::TextureType::EMISSIVE)
				nr = std::to_string(aux_emissive++);
			this->shader.setInt((mat+name+nr).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures.at(i).texture);
		}
		glActiveTexture(Resources::TextureUnitMap.at(0));
	}
}

void Mesh::draw()
{
	bindTextures();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}