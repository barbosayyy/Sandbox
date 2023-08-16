#pragma once

#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>

class Texture
{
public:
	Texture();
	~Texture();

	unsigned int texture;
private:
	int width;
	int height;
	int nrOfchannels;
	unsigned char* data = nullptr;

	void load();
};