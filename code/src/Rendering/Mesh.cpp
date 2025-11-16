#include "Mesh.h"
#include "Core/Debug.h"
#include "Core/Types.h"
#include "OpenGL/GLBuffer.h"
#include "Resources/ResourceManagement.h"
#include <string>

#include "Rendering/OpenGL/GLBuffer.h"
#include "Texture.h"

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
		this->_material._shader = ResourceManagement::LoadShader("common/shaders/GeometryPass.vert", "common/shaders/GeometryPass.frag");
	}

	void Mesh::Draw(Renderer* renderer, vec3 pos, vec3 rot, vec3 scale) {

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
		modelM = glm::scale(modelM, scale);

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
			_material._shader->SetInt(String("specular" + std::to_string(txCurrent)), _material._specularMap.id);
			glBindTexture(GL_TEXTURE_2D, _material._specularMap.id);
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

	void Mesh::SetTextureMap(u32 assetID, TextureType type) {
		switch(type) {
			case(TextureType::DIFFUSE):
				_material._diffuseMap.id = assetID;
			break;
			case(TextureType::SPECULAR):
				_material._specularMap.id = assetID;
			break;
			case(TextureType::NORMAL):
				_material._normalMap.id = assetID;
			break;
			case(TextureType::EMISSIVE):
				_material._emissionMap.id = assetID;
			break;
		}
	}
}

