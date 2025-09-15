#include "Mesh.h"
#include "Core/Types.h"
#include "OpenGL/GLBuffer.h"
#include "Texture.h"
#include "Resources/ShaderManager.h"
#include <string>

#include "Rendering/OpenGL/GLBuffer.h"

namespace Sb {

	Mesh::Mesh() {}

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

		if(_material._diffuseMap.GetID() > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("diffuse" + std::to_string(txCurrent)), _material._diffuseMap.GetID());
			glBindTexture(GL_TEXTURE_2D, _material._diffuseMap.GetID());
			txCurrent = 0;
		}
		
		if(_material._specularMap.GetID() > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("specular" + std::to_string(txCurrent)), _material._diffuseMap.GetID());
			glBindTexture(GL_TEXTURE_2D, _material._diffuseMap.GetID());
			txCurrent = 0;
		}

		if(_material._normalMap.GetID() > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("normal" + std::to_string(txCurrent)), _material._normalMap.GetID());
			glBindTexture(GL_TEXTURE_2D, _material._normalMap.GetID());
			txCurrent = 0;
		}

		if(_material._emissionMap.GetID() > 0) {
			glActiveTexture(GL_TEXTURE0+txActive);
			txActive++;
			txCurrent++;
			_material._shader->SetInt(String("emissive" + std::to_string(txCurrent)), _material._emissionMap.GetID());
			glBindTexture(GL_TEXTURE_2D, _material._emissionMap.GetID());
			txCurrent = 0;
		}

		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetTextureMap(u32 textureID, TextureType textureType) {
		if(textureType == TextureType::DIFFUSE){
			this->_material._diffuseMap.SetID(textureID);
		}
		else if(textureType == TextureType::SPECULAR) {
			this->_material._specularMap.SetID(textureID);
		}
		else if(textureType == TextureType::NORMAL) {
			this->_material._normalMap.SetID(textureID);
		}
		else if(textureType == TextureType::EMISSIVE) {
			this->_material._emissionMap.SetID(textureID);
		}
	}
}

