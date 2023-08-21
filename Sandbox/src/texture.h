#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>

using ImageType = enum {
	JPG, PNG
};

class Texture
{
public:
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