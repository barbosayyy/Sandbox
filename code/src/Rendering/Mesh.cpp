#include "Mesh.h"
#include "Texture.h"

using namespace Sb;

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
		int i {0};
		String n {""};
		String name {""};
		for (Texture texture : _textures)
		{
			glActiveTexture(textureUnitMap.at(i));
			
			std::map<TextureType, String>::iterator it;
			it = textureTypeMap.find(texture.GetType());
			name = it->second;
			//// TODO this can be refactored by casting String
			//String nr;
			//String name = it->second;
			if (it->first == TextureType::DIFFUSE)
				n = std::to_string(tmpDiffuse++);
			else if(it->first == TextureType::SPECULAR)
				n = std::to_string(tmpSpecular++);
				
			shader->SetInt(String(String("texture_")+name+n).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, _textures.at(i).GetID());
			i++;
		}
		glActiveTexture(textureUnitMap.at(0));
	}
}

void Mesh::Draw(Shader* shader, Renderer* renderer, vec3 pos)
{
	//BindTextures(shader);
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	//glBindVertexArray(_vao);
	//glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
	//glActiveTexture(GL_TEXTURE0);

	u8 i = 0;
    u8 j = 0;
    u8 diff = 1;
    u8 spec = 1;
    String num = "";
    String name = "";
    std::map<TextureType, String>::iterator it;
	if(shader != nullptr){
		shader->Use();
		shader->SetMat4("view", renderer->GetRenderCamera()->GetView());
		shader->SetMat4("projection", renderer->GetProjection());
		// TODO: Apply inverse transponse only when detecting changes in position rotation and scale
		mat4 modelM {1.0f};
		modelM = glm::translate(modelM, pos);
		modelM = glm::scale(modelM, vec3(1.0f,1.0f,1.0f));
		shader->SetMat4("model", modelM);
	}
	if (this->_textures.size() > 0){
		for (Texture tex : this->_textures)
		{
			glActiveTexture(textureUnitMap.at(j));
			it = textureTypeMap.find(tex.GetType());
			name = it->second;
			if(it->first == TextureType::DIFFUSE){
				num = std::to_string(diff++);
			}
			else if(it->first == TextureType::SPECULAR){
				num = std::to_string(spec++);
			}
			shader->SetInt(String(name + num).c_str(), j);
			glBindTexture(GL_TEXTURE_2D, tex.GetID());
			j++;
		}
	}
	i++;

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}