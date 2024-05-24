#pragma once

#include <iostream>
#include <string_view>
#include <vector>
#include <map>
#include "../Core/Singleton.h"
#include "../Core/Types.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>

	// TODO
	// Aliases for texture types and image format
	// Just load texture directly ? 

namespace Sandbox{
	static std::map<uint8_t, GLenum> textureUnitMap{
		{0, GL_TEXTURE0},
		{1, GL_TEXTURE1},
		{2, GL_TEXTURE2},
		{3, GL_TEXTURE3},
		{4, GL_TEXTURE4},
		{5, GL_TEXTURE5},
		{6, GL_TEXTURE6},
		{7, GL_TEXTURE7},
		{8, GL_TEXTURE8},
		{9, GL_TEXTURE9},
		{10, GL_TEXTURE10},
		{11, GL_TEXTURE11},
		{12, GL_TEXTURE12},
		{13, GL_TEXTURE13},
		{14, GL_TEXTURE14},
		{15, GL_TEXTURE15}
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
		int _nrOfChannels;
		unsigned int _id;
		TextureType _type;

	public:
		String _name;
		Texture(const char* path, TextureType tType, GLint wrapMethod, bool flipVertical, bool gammaCorrection);
		//Texture() {};
		~Texture();

		unsigned int GetID() const {return _id;};
		TextureType GetType() const {return _type;};
		int GetNrOfChannels() const {return _nrOfChannels;};

		unsigned int& SetID() {return _id;};
		TextureType& SetType() {return _type;};

	};

	class TextureManager : public Singleton<TextureManager, int>{
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