#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "../Core/Singleton.h"
#include "../Core/Types.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>

// TODO
// Aliases for texture types and image types

// !!! - This is not needed, just load texture directly ? 

namespace Sandbox{
	static std::map<uint8_t, GLenum> textureUnitMap{
		{0, GL_TEXTURE0},
		{1, GL_TEXTURE1},
		{2, GL_TEXTURE2},
		{3, GL_TEXTURE3},
		{4, GL_TEXTURE4},
		{5, GL_TEXTURE5},
		{6, GL_TEXTURE6},
		{7, GL_TEXTURE7}
	};
	static std::map<TextureType, String> textureTypeMap{
	{TextureType::DIFFUSE, "diffuse"},
	{TextureType::SPECULAR,"specular"},
	{TextureType::EMISSIVE,"emissive"},
	};

	class Texture
	{
	private:
		int _width;
		int _height;
		int _nrOfchannels;
		unsigned char* _data = nullptr;

		void Load(const char* texturePath, ImageFormat imageType, GLint texWrapMethod);
	public:
		Texture();
		Texture(const char* texturePath, ImageFormat imageType, TextureType textureType, GLint texWrapMethod);
		~Texture();

		unsigned int _texture;
		TextureType _type;
	};

	class 
	TextureManager : public Singleton<TextureManager, int>{
		private:
			std::vector<Texture> _textures;
		public:
			TextureManager();
			~TextureManager();
			const Texture& GetTexture(int textureId) const;
			void AddTexture(Texture& newTexture);
			void RemoveTexture(int textureId);
	};
}