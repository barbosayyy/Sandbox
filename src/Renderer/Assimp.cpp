#include "Assimp.h"
#include "../Core/Debug.h"

namespace Sandbox{

	std::vector<Texture> LoadAssimpMaterialTextures(aiMaterial* mat, aiTextureType type){
		Logger::Trace(LogLevel::RUNTIME, "Assimp Texture Loader: ", "Loading material textures...");
		std::vector<Texture> textures;
		for(u32 i; i < mat->GetTextureCount(type); i++){
			aiString str;
			mat->GetTexture(type, type, &str);
			//TEMP: pass PNG format for now
			//TEMP: Here a request must be made to texture manager for a new txture or already existing one
			Texture texture(str.C_Str(), ImageFormat::PNG, TextureType(type), GL_REPEAT);
			textures.push_back(texture);
		}
		return textures;
	}

	Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene){
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
		Debugger::Print("Processing assimp mesh");
		for(u32 i = 0; i < mesh->mNumVertices; i++){
			Vertex vertex;
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z; 
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;

			vertices.push_back(vertex);
		}
		Debugger::Print("ok");
		for(u32 i = 0; i < mesh->mNumFaces; i++){
			Debugger::Print("Going thru faces");
			aiFace face = mesh->mFaces[i];
			for(u32 j = 0; j < face.mNumIndices; j++){
				Debugger::Print("Going thru indices");
				indices.push_back(face.mIndices[j]);
			}
		}
		if(mesh->mMaterialIndex >= 0){
			Debugger::Print("Material index");
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = LoadAssimpMaterialTextures(mat, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = LoadAssimpMaterialTextures(mat, aiTextureType_SPECULAR);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}
		if(vertices.size() > 0 && indices.size() > 0)
		{
			Logger::Trace(LogLevel::RUNTIME, "Assimp Mesh Process: ", "Successfully processed Mesh");
		}
		else{
			Debugger::Print("Returning a mesh");
		}
		return Mesh(vertices, indices, textures);
	}
}
