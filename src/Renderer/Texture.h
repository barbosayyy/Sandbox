#pragma once

#include <iostream>
#include <vector>
#include "../Core/Singleton.h"
#include "../Core/Types.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>

// TODO
// Aliases for texture types and image types

// !!! - This is not needed, just load texture directly ?

namespace Sandbox{
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