#pragma once

#include <iostream>
#include "types.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>

// TODO
// Aliases for texture types and image types

// !!! - This is not needed, just load texture directly ?
class Texture
{
public:
	enum class ImageType {
		JPG, PNG
	};
	enum class TextureType {
		SPECULAR, DIFFUSE, EMISSIVE
	};

	Texture();
	Texture(const char* texturePath, ImageType imageType, TextureType textureType, GLint texWrapMethod);
	~Texture();

	unsigned int texture;
	TextureType type;
private:
	int width;
	int height;
	int nrOfchannels;
	unsigned char* data = nullptr;

	void load(const char* texturePath, ImageType imageType, GLint texWrapMethod);
};