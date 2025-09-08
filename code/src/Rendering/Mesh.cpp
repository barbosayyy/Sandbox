#include "Mesh.h"
#include "OpenGL/GLBuffer.h"
#include "Texture.h"
#include "Resources/ShaderManager.h"
#include <string>

#include "Rendering/OpenGL/GLBuffer.h"

namespace Sb {

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, NewMaterial material) : _vertices(vertices), _indices(indices), _material(material) {
		CreateMesh();
	}

	Mesh::~Mesh() {

	}

	void Mesh::CreateMesh()	{
		
		GLBufferVertexData(this->_vao, this->_vertices, this->_indices);

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

