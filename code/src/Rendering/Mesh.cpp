#include "Mesh.h"
#include "Core/Types.h"
#include "OpenGL/GLBuffer.h"
#include "Resources/ResourceManager.h"
#include <string>

#include "Rendering/OpenGL/GLBuffer.h"

namespace Sb {

	Mesh::Mesh() {}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, Material material) : _vertices(vertices), _indices(indices), _material(material) {
		CreateMesh();
	}

	Mesh::~Mesh() {

	}

	void Mesh::CreateMesh()	{
		
		GLBufferVertexData(this->_vao, this->_vertices, this->_indices);

		Renderer& ren = Renderer::GetInstance();
		ResourceManagement::ResourceManager& res = ResourceManagement::ResourceManager::GetInstance();
		this->_material._shader = res.LoadShader(38, 39);
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

		if(_material._diffuseMap.id > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("diffuse" + std::to_string(txCurrent)), _material._diffuseMap.id);
			glBindTexture(GL_TEXTURE_2D, _material._diffuseMap.id);
			txCurrent = 0;
		}
		
		if(_material._specularMap.id > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("specular" + std::to_string(txCurrent)), _material._diffuseMap.id);
			glBindTexture(GL_TEXTURE_2D, _material._diffuseMap.id);
			txCurrent = 0;
		}

		if(_material._normalMap.id > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("normal" + std::to_string(txCurrent)), _material._normalMap.id);
			glBindTexture(GL_TEXTURE_2D, _material._normalMap.id);
			txCurrent = 0;
		}

		if(_material._emissionMap.id > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("emissive" + std::to_string(txCurrent)), _material._emissionMap.id);
			glBindTexture(GL_TEXTURE_2D, _material._emissionMap.id);
			txCurrent = 0;
		}

		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetTextureMap(u32 textureID, TextureType textureType) {
		if(textureType == TextureType::DIFFUSE){
			this->_material._diffuseMap.id = textureID;
		}
		else if(textureType == TextureType::SPECULAR) {
			this->_material._specularMap.id = textureID;
		}
		else if(textureType == TextureType::NORMAL) {
			this->_material._normalMap.id = textureID;
		}
		else if(textureType == TextureType::EMISSIVE) {
			this->_material._emissionMap.id = textureID;
		}
	}
}

