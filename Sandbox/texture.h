#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glfw3.h"

class Texture
{
public:
	Texture();
	~Texture();
private:
	int width;
	int height;
	int nrOfchannels;
	unsigned char* data = nullptr;
	unsigned int texture;

	void load();
};