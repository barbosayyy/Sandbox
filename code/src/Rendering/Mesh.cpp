#include "Mesh.h"
#include "Core/Types.h"
#include "Rendering/Texture.h"
#include "Resources/ShaderManager.h"
#include <string>

namespace Sb {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, NewMaterial material) : _vertices(vertices), _indices(indices), _material(material) {
		CreateMesh();
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, NewMaterial material) : _vertices(vertices), _indices(indices), _material(material) {
		CreateMesh();
	}

	Mesh::~Mesh() {

	}

	void Mesh::CreateMesh()	{
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		if(_vertices.size() > 0) {
			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
		}
		else {
			std::cout << "Mesh_createMesh: Vertex vector is empty!" << std::endl;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
		if (_vertices.size() > 0) {
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
			glEnableVertexAttribArray(2);
		}
		glBindVertexArray(0);

		Renderer& ren = Renderer::GetInstance();
		this->_material._shader = ren._shaderManager.GetShader(3, 4);
	}

	void Mesh::Draw(Renderer* renderer, vec3 pos) {

		int txActive = 0;
		int txCurrent = 0;

		if(_material._shader == nullptr) {
			return;
		}

		_material._shader->Use();
		_material._shader->SetMat4("view", renderer->GetRenderCamera()->GetView());
		_material._shader->SetMat4("projection", renderer->GetRenderCamera()->GetProjection());
		// TODO: Apply inverse transponse only when detecting changes in position rotation and scale
		mat4 modelM {1.0f};
		modelM = glm::translate(modelM, pos);
		modelM = glm::scale(modelM, vec3(1.0f,1.0f,1.0f));
		_material._shader->SetMat4("model", modelM);

		for(int i = 0 ; i < (int)TextureType::EMISSIVE; i++) {
			
			if(i == (int)TextureType::DIFFUSE) {
				if(_material._diffuseMap.size() > 0) {
					for(Texture tex : _material._diffuseMap) {
						glActiveTexture(GL_TEXTURE0+txActive);
						txActive++;
						txCurrent++;
						_material._shader->SetInt(String("diffuse" + std::to_string(txCurrent)), tex.GetID());
						glBindTexture(GL_TEXTURE_2D, tex.GetID());
					}
				}
			}
			else if(i == (int)TextureType::SPECULAR) {
				if(_material._specularMap.size() > 0) {
					for(Texture tex : _material._specularMap) {
						glActiveTexture(GL_TEXTURE0+txActive);
						txActive++;
						txCurrent++;
						_material._shader->SetInt(String("specular" + std::to_string(txCurrent)), tex.GetID());
						glBindTexture(GL_TEXTURE_2D, tex.GetID());
					}
				}
			}
			else if(i == (int)TextureType::NORMAL) {
				if(_material._normalMap.size() > 0) {

				}
			}
			else if(i == (int)TextureType::EMISSIVE) {
				if(_material._emissionMap.size() > 0) {

				}
			}
			txCurrent = 0;
		}

		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}
}

