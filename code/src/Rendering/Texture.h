#pragma once

#include <iostream>
#include <string_view>
#include <vector>
#include <map>
#include "Core/Singleton.h"
#include "Core/Types.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>

	// TODO
	// Aliases for texture types and image format
	// Just load texture directly ? 

namespace Sb {

	class Texture{
	private:
		int _width;
		int _height;
		int _nrOfChannels;
		unsigned int _id;
		TextureType _type;

	public:
		String _name;
		Texture(const char* path, TextureType tType, GLint wrapMethod, bool flipVertical, bool gammaCorrection);
		~Texture();

		unsigned int GetID() const {return _id;};
		TextureType GetType() const {return _type;};
		int GetNrOfChannels() const {return _nrOfChannels;};

		unsigned int& SetID() {return _id;};
		TextureType& SetType() {return _type;};
	};
}