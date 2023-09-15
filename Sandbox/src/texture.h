#pragma once

#include <iostream>
#include <glew/glew.h>
#include <glfw/glfw3.h>

// !!! - This is not needed, just load texture directly ?
class Texture
{
public:
	enum class ImageType {
		JPG, PNG
	};

	Texture();
	Texture(const char* texturePath, ImageType imageType, GLint texWrapMethod);
	~Texture();

	unsigned int texture;
private:
	int width;
	int height;
	int nrOfchannels;
	unsigned char* data = nullptr;

	void load(const char* texturePath, ImageType imageType, GLint texWrapMethod);
};